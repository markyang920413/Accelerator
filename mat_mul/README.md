#### 파일 설명
> Makefile	<br />
> OpenCl.stderr - Thor에 OpenCL로 돌렸을때 생기는 오류 <br />
> OpenCl.stdout	-       "                   결과값 <br />
> kernel.cl	 - OpenCL C 프로그래밍 언어<br />
> mat_mul.c	 - 기본 행렬 연산 코드 뒤에 0을 붙이면 sequential code 1을 붙이면 OpenCl 코드 실행<br />
> mat_mul_opencl.c	- C 기반의 호스트 프로그램 <br />
> mat_mul_opencl_analysis.c	- C 기반의 호스트 프로그램<br />
  mat_mul_opencl_openblas.c - OpenBLAS 활용
> mat_mul_seq.c	- Seuquential Code<br />
> sequential.stderr	 오류 값<br />
> sequential.stdout  Sequential 으로 했을 때 나오는 결과값<br />

[스크린샷](https://www.evernote.com/l/AuGHdkdWHCtNy7uVnQzdLp1s8Ck696Roczw)


OpenCL automatical Matmul experiment 
===================================

# You can control local_size in test.sh
```console
vim test.sh
line 2: arr=([Write here what you want local_size])

line 8: while [ $j -lt [Write here that How do you want to do each experiment agin] ]
```

# How to do experiment
```console
./tese.sh
```

then, ./mat_mul 1 will be execute and make a successed.txt and convert.txt




