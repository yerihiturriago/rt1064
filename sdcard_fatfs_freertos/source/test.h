

#ifndef TEST_H_
#define TEST_H_


#include "global.h"


void test_FileAccessTask1(void *pvParameters);
void test_FileAccessTask2(void *pvParameters);
void test_fileSystem(void);

void test_playBullet(void);
static void test_thrdPlayBullet(void* arg);

void test_loadSawWave(void);
void test_loadInRam32MB(void);
static void test_thrdLoadInRam32MB(void* arg);
void test_playSnareSequence(void);
void test_adc(void);

#endif









