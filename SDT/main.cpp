#include <stdio.h>
#include <time.h>
#include <iostream>
using namespace std;
#define MAX_DOUBLE 1.79769e+308
#define E 2
 
struct point
{
	int x;
	double y;
};
 
void compress()
{
	FILE * fin = fopen("/Users/rabbit0v0/PycharmProjects/extract/avg5.txt", "r");
	FILE * fout = fopen("/Users/rabbit0v0/CLionProjects/SDT/out.txt", "w");

	double up_gate = -MAX_DOUBLE;         
	double down_gate = MAX_DOUBLE;

	double now_up, now_down;	
	
	double data = 0;
	double last_read_data;
	double last_stored_data;
 
	//read and save the first data
	fscanf(fin, "%lf", &last_stored_data);
	fprintf(fout, "0 %.2lf ", last_stored_data);
	
	last_read_data =  last_stored_data;
	
	int last_stored_t = 0;

	int t=0;
 	while(++t, fscanf(fin, "%lf", &data) != EOF)
 	{
	 	now_up = double(data-last_stored_data-E) / (t-last_stored_t);
	 	if(now_up > up_gate)
	 		up_gate = now_up;
 
 		now_down = double(data-last_stored_data+E) / (t-last_stored_t);
 		if(now_down < down_gate)
 			down_gate = now_down;
 
 		if(up_gate >= down_gate)
		{
			fprintf(fout, "%d %.2lf ", t-1, last_read_data);
			last_stored_t = t-1;
			last_stored_data = last_read_data;

		 	up_gate = double(data-last_stored_data-E);
		 	down_gate = double(data-last_stored_data+E);
		}
		last_read_data = data;
 	}
	fprintf(fout, "%d %.2lf ", t-1, last_read_data);
	
	fclose(fin);
	fclose(fout);
}
 
void uncompress()
{
	FILE * fin = fopen("/Users/rabbit0v0/CLionProjects/SDT/out.txt", "r");
	FILE * fout = fopen("/Users/rabbit0v0/CLionProjects/SDT/src.txt", "w");
 
	point a,b;	
	fscanf(fin, "%d %lf", &a.x, &a.y);
	
	while(fscanf(fin, "%d %lf", &b.x,&b.y) != EOF)
	{
		fprintf(fout, "%.2lf ", a.y);

		if(a.x+1 != b.x)
		{
			double k = double(b.y - a.y) / (b.x - a.x);
			for(int i=a.x+1; i<b.x; i++)
			{
				fprintf(fout, "%.2lf ", k*(i-a.x) + a.y);
			}
		}
 
		a.x = b.x;
		a.y = b.y;
	}
	fprintf(fout, "%.2lf ", b.y);
	fclose(fin);
	fclose(fout);
}
 
int main()
{
    clock_t st1, end1, end2;
    st1 = clock();
    cout << st1 << '\n';
	compress();
	end1 = clock();
	cout << end1 << '\n';
	uncompress();
	end2 = clock();
	cout << end1-st1 << " " << end2-end1;
	return 0;
}
/*
 T2 now_up, now_down;
 
 T2 data_ = 0;
 T2 last_read_data;
 T2 last_stored_data;
 //    T1 last_stored_t;
 //    T1 last_read_t;
 
 int size = t->size();
 std::vector<T1> ans_t;
 std::vector<T2> ans_x;
 
 if (x->isFastMode()){
 T2* start_x;
 start_x = (T2*)x->getDataArray();
 last_read_data = start_x[0];
 last_stored_data = last_read_data;
 ans_x.insert(last_read_data);
 if (t->isFastMode()){
 T1* start_t;
 start_t = (T1*)t->getDataArray();
 last_stored_t = start_t[0];
 last_read_t = last_stored_t;
 ans_t.insert(last_stored_t);
 //            T1 now_t;
 int i = 1;
 while(i < size){
 data_ = start_x[i];
 now_t = start_t[i];
 now_up = double(data_-last_stored_data-E)/(now_t-last_stored_t);
 if (now_up>up_gate)
 up_gate = now_up;
 now_down = double(data_-last_stored_data+E)/(now_t-last_stored_t);
 if (now_down<down_gate)
 down_gate = now_down;
 if (up_gate >= down_gate){
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 
 last_stored_t = last_read_t;
 last_stored_data = last_read_data;
 
 up_gate = double(data_-last_stored_data-E);
 down_gate = double(data_-last_stored_data+E);
 }
 i++;
 last_read_data = data_;
 last_read_t = now_t;
 }
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 }
 else{
 T1** segment_t;
 segment_t = (T1**)t->getDataSegment();
 int segment_size = t->getSegmentSize();
 last_stored_t = segment_t[0][0];
 last_read_t = last_stored_t;
 ans_t.insert(last_stored_t);
 //            T1 now_t;
 int i = 1;
 int c = 0, index = 1;
 while(i < size){
 data_ = start_x[i];
 now_t = segment_t[c][index];
 now_up = double(data_-last_stored_data-E)/(now_t-last_stored_t);
 if (now_up>up_gate)
 up_gate = now_up;
 now_down = double(data_-last_stored_data+E)/(now_t-last_stored_t);
 if (now_down<down_gate)
 down_gate = now_down;
 if (up_gate>=down_gate){
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 
 last_stored_t = last_read_t;
 last_stored_data = last_read_data;
 
 up_gate = double(data_-last_stored_data-E);
 down_gate = double(data_-last_stored_data+E);
 }
 i++;
 c = i/segment_size;
 index = i%segment_size;
 last_read_data = data_;
 last_read_t = now_t;
 }
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 }
 }
 else{
 T2** segment_x;
 segment_x = (T2**)x->getDataSegment();
 last_read_data = segment_x[0][0];
 last_stored_data = last_read_data;
 ans_x.insert(last_read_data);
 int c = 0, index = 1;
 int segment_size = x->getSegmentSize();
 if (t->isFastMode()){
 T1* start_t;
 start_t = (T1*)t->getDataArray();
 last_stored_t = start_t[0];
 last_read_t = last_stored_t;
 ans_t.insert(last_stored_t);
 //            T1 now_t;
 int i = 1;
 while(i < size){
 data_ = segment_x[c][index];
 now_t = start_t[i];
 now_up = double(data_-last_stored_data-E)/(now_t-last_stored_t);
 if (now_up>up_gate)
 up_gate = now_up;
 now_down = double(data_-last_stored_data+E)/(now_t-last_stored_t);
 if (now_down<down_gate)
 down_gate = now_down;
 if (up_gate >= down_gate){
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 
 last_stored_t = last_read_t;
 last_stored_data = last_read_data;
 
 up_gate = double(data_-last_stored_data-E);
 down_gate = double(data_-last_stored_data+E);
 }
 i++;
 c = i/segment_size;
 index = i%segment_size;
 last_read_data = data_;
 last_read_t = now_t;
 }
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 }
 else{
 T1** segment_t;
 segment_t = (T1**)t->getDataSegment();
 int segment_size1 = t->getSegmentSize();
 last_stored_t = segment_t[0][0];
 int c1 = 0, index1 = 1;
 last_read_t = last_stored_t;
 ans_t.insert(last_stored_t);
 //            T1 now_t;
 int i = 1;
 while(i < size){
 data_ = segment_x[c][index];
 now_t = segment_t[c1][index1];
 now_up = double(data_-last_stored_data-E)/(now_t-last_stored_t);
 if (now_up>up_gate)
 up_gate = now_up;
 now_down = double(data_-last_stored_data+E)/(now_t-last_stored_t);
 if (now_down<down_gate)
 down_gate = now_down;
 if (up_gate>=down_gate){
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 
 last_stored_t = last_read_t;
 last_stored_data = last_read_data;
 
 up_gate = double(data_-last_stored_data-E);
 down_gate = double(data_-last_stored_data+E);
 }
 i++;
 c = i/segment_size;
 index = i%segment_size;
 c1 = i/segment_size1;
 index1 = i%segment_size1;
 last_read_data = data_;
 last_read_t = now_t;
 }
 ans_t.insert(last_read_t);
 ans_x.insert(last_read_data);
 }
 }
 */
