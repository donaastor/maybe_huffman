#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <algorithm>
#include <functional>

#define DOUBLE 1

#if DOUBLE==1
typedef uint32_t z1;
typedef uint64_t z2;
#else
typedef uint16_t z1;
typedef uint32_t z2;
#endif

#if __cplusplus >= 202002L
#include <bit>
inline uint32_t bwid(z2 x){
	return (uint32_t)std::bit_width(x);
}
#else
inline uint32_t bwid(z2 x){
	uint32_t w=0;
	z2 d=1;
	while(d<=x){
		d<<=1;
		++w;
	}return w;
}
#endif

uint64_t ht(uint32_t n,z1 *f,z1 *h){
	z1 pf=f[0];
	z1 ph=h[0]=32;
	z2 cs=0x100000000ull;
	z2 ts=0x100000000ull;
	for(uint32_t i=1;i<n;++i){
		if(f[i-1]<=pf-f[i]){
			pf=f[i];
			--ph;
			cs>>=1;
		}
		h[i]=ph;
		ts+=cs;
	}
	uint32_t bts=bwid(ts);
	z2 ex=(1ull<<bts)-ts;
	for(uint32_t i=0;i<n;++i){
		z2 cv=1ull<<h[i];
		if(cv<=ex){
			ex-=cv;
			++h[i];
		}
	}
	++bts;
	for(uint32_t i=0;i<n;++i)
		h[i]=bts-h[i];
	uint64_t r=0;
	for(uint32_t i=0;i<n;++i)
		r+=f[i]*(uint64_t)h[i];
	return r;
}

#define mlen 1024
z1 f[mlen];
z1 h[mlen];
int main(int args,char **argv){
	if(args==1)return 1;
	uint32_t n=args-1;
	for(uint32_t i=0;i<n;++i)
		f[i]=atoi(argv[i+1]);
	std::sort(f,f+n,std::greater<z1>());
	for(uint32_t i=1;i<n;++i)
	if((f[i]==0)&(f[i-1]==0)){
		n=i;
		break;
	}
	uint64_t score=ht(n,f,h);
	for(uint32_t i=0;i<n;++i)
		printf("%3u",f[i]);
	printf("\n");
	for(uint32_t i=0;i<n;++i)
		printf("%3u",h[i]);
	printf("\n");
	printf("%lu\n",score);
	return 0;
}
