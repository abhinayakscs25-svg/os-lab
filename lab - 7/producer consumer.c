#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

HANDLE mutex;
HANDLE empty;
HANDLE full;

// Producer
DWORD WINAPI producer(LPVOID arg) {
    int item;

    while (1) {
        item = rand() % 100;

        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        buffer[in] = item;
        printf("Producer produced item %d at index %d\n", item, in);

        in = (in + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(full, 1, NULL);

        Sleep(1000);
    }
}

// Consumer
DWORD WINAPI consumer(LPVOID arg) {
    int item;

    while (1) {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(mutex, INFINITE);

        item = buffer[out];
        printf("Consumer consumed item %d from index %d\n", item, out);

        out = (out + 1) % BUFFER_SIZE;

        ReleaseMutex(mutex);
        ReleaseSemaphore(empty, 1, NULL);

        Sleep(1000);
    }
}

int main() {
    HANDLE p, c;

    mutex = CreateMutex(NULL, FALSE, NULL);
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

    p = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    c = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(p, INFINITE);
    WaitForSingleObject(c, INFINITE);

    return 0;
}
