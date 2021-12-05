#ifndef HIST_H_
#define HIST_H_

void GetHist(BYTE* input, int* hist, int width, int height);

void CumulativeHist(int* stackHist, int* hist);

void HistEqual(BYTE* input, BYTE* output, int* stackHist, int width, int height);

#endif /* HIST_H_ */