/******
x * y = ans
******/
#define cp complex<double>

const int maxn=131072+5;
const double pi=acos(-1);

struct FastFourierTransform {
	int n;
	cp omega[maxn],iomega[maxn];
	
	void init(int n) {
		this->n=n;
		for(int i=0; i<n; i++) {
			omega[i]=cp(cos(2*pi/n*i),sin(2*pi/n*i));
			iomega[i]=conj(omega[i]); //共轭复数
		}
	}
	
	void transform(cp* a,cp* omega) {
		int k=log2(n);
		for(int i=0; i<n; i++) { //二进制位翻转
			int t=0;
			for(int j=0; j<k; j++)if(i&(1<<j))t|=(1<<(k-j-1));
			if(i<t)swap(a[i],a[t]); //避免多次翻转
		}
		for(int len=2; len<=n; len*=2) {
			int mid=len>>1;
			for(cp* p=a; p!=a+n; p+=len)
				for(int i=0; i<mid; i++) {
					cp t=omega[n/len*i]*p[mid+i];
					p[mid+i]=p[i]-t;
					p[i]+=t;
				}
		}
	}

	void dft(cp* a) {
		transform(a,omega);
	}

	void idft(cp* a) {
		transform(a,iomega);
		for(int i=0; i<n; i++)a[i]/=n;
	}
} fft;

void Multiply(const int* a1,const int n1,const int* a2,const int n2,int* ans) {
	int n=1;
	while(n<n1+n2)n<<=1; //补成整数
	static cp c1[maxn],c2[maxn];
	for(int i=0; i<n1; i++)c1[i].real(a1[i]);
	for(int i=0; i<n2; i++)c2[i].real(a2[i]);
	fft.init(n);
	fft.dft(c1);
	fft.dft(c2);
	for(int i=0; i<n; i++)c1[i]*=c2[i];
	fft.idft(c1);
	for(int i=0; i<n1+n2-1; i++)ans[i]=round(c1[i].real());
}

int n,a1[maxn],a2[maxn],ans[maxn];
char s1[maxn],s2[maxn];

int main() {
	n=Get_Int();
	scanf("%s",s1);
	scanf("%s",s2);
	for(int i=0; i<n; i++)a1[n-i-1]=s1[i]-'0';
	for(int i=0; i<n; i++)a2[n-i-1]=s2[i]-'0';
	Multiply(a1,n,a2,n,ans);
	for(int i=0; i<2*n-1; i++) {
		ans[i+1]+=ans[i]/10;
		ans[i]%=10;
	}
	int len=2*n-1;
	while(!ans[len])len--;
	for(int i=len; i>=0; i--)printf("%d",ans[i]);
	return 0;
}