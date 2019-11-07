// Nama/NIM     : Jonathan Yudi Gunawan/13518084
// Hari, Tanggal  : Selasa, 29 Oktober 2019
// Topik/Deskripsi  : Variasi List Linier/ADT List Rekursif nya Tuan Yon

#include <stdio.h>
#include <stdlib.h>
#include "listrek.h"

#define max(a, b) a>b?a:b
#define min(a, b) a<b?a:b
#define abs(a) a<0?-a:a 
#define selisih(a, b) abs(a-b)
#define swap(a,b) {infotype tmp; tmp = b; b = a; a = tmp;}

#define intput(a)     scanf("%d", &a)
#define intput2(a,b)  scanf("%d %d", &a, &b)
#define charput(a)    scanf(" %c", &a)
#define print(a)      printf("%d", a)
#define prints(a)     printf("%d ", a)
#define println(a)    printf("%d\n", a)
#define ENDL          printf("\n")

#define fori(i, n) for(int i = 0; i < n; i++)
#define forii(i, s, e) for(int i = s; i < e; i++)

/* *** Manajemen Memori *** */
address Alokasi (infotype X)
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak Nil, dan misalnya menghasilkan P, 
  maka Info(P) = X, Next(P) = Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
	address P = (address) malloc(sizeof(address));
	if(P == Nil) return Nil;
	Info(P) = X;
	Next(P) = Nil;
	return P;
}

void Dealokasi (address P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */
{
	free(P);
}

/* *** Primitif-primitif yang harus direalisasikan *** */

/* Pemeriksaan Kondisi List */
int IsEmpty(List L)
/* Mengirimkan 1 jika L kosong dan 0 jika L tidak kosong */
{
	return L == Nil;
}

int IsOneElmt(List L)
/* Mengirimkan 1 jika L berisi 1 elemen dan 0 jika > 1 elemen atau kosong */
{
	if(IsEmpty(L)) return 0;
	return Next(L) == Nil;
}

/* *** Selektor *** */
infotype FirstElmt (List L)
/* Mengirimkan elemen pertama sebuah list L yang tidak kosong */
{
	return Info(L);
}

List Tail(List L)
/* Mengirimkan list L tanpa elemen pertamanya, mungkin menjadi list kosong */
{
	return Next(L);
}

/* *** Konstruktor *** */
List Konso(infotype e, List L)
/* Mengirimkan list L dengan tambahan e sebagai elemen pertamanya. 
e dialokasi terlebih dahulu. Jika alokasi gagal, mengirimkan L. */
{
	List P = Alokasi(e);
	if(P == Nil) return L;
	Next(P) = L;
	return P;
}

List KonsB(List L, infotype e)
/* Mengirimkan list L dengan tambahan e sebagai elemen pertamanya */
/* e harus dialokasi terlebih dahulu */
/* Jika alokasi e gagal, mengirimkan L */ 
{
	List P = Alokasi(e);
	if(P == Nil) return L;
	if(IsEmpty(L)) return P;
	Next(L) = KonsB(Tail(L), e);
	return L;
}

/* *** Operasi Lain *** */
List Copy (List L)
/* Mengirimkan salinan list L (menjadi list baru) */
/* Jika ada alokasi gagal, mengirimkan L */ 
{
	if(IsEmpty(L)) return Nil;
	return Konso(FirstElmt(L), Copy(Tail(L)));
}

void MCopy (List Lin, List *Lout)
/* I.S. Lin terdefinisi */
/* F.S. Lout berisi salinan dari Lin */
/* Proses : menyalin Lin ke Lout */
{
	*Lout = Copy(Lin);
}

List Concat (List L1, List L2)
/* Mengirimkan salinan hasil konkatenasi list L1 dan L2 (menjadi list baru) */
/* Jika ada alokasi gagal, menghasilkan Nil */
{
	if(IsEmpty(L1)) return Copy(L2);
	return Konso(FirstElmt(L1), Concat(Tail(L1), L2));
}

void MConcat (List L1, List L2, List *LHsl)
/* I.S. L1, L2 terdefinisi */
/* F.S. LHsl adalah hasil melakukan konkatenasi L1 dan L2 dengan cara "disalin" */
/* Proses : Menghasilkan salinan hasil konkatenasi list L1 dan L2 */
{
	*LHsl = Concat(L1, L2);
}

void PrintList (List L)
/* I.S. L terdefinisi. */
/* F.S. Setiap elemen list dicetak. */
{
	if(IsEmpty(L)) return;
	println(Info(L));
	PrintList(Tail(L));
}

int NbElmtList (List L)
/* Mengirimkan banyaknya elemen list L, Nol jika L kosong */
{
	if(IsEmpty(L)) return 0;
	return 1 + NbElmtList(Tail(L));
}
boolean Search (List L, infotype X)
/* Mengirim true jika X adalah anggota list, false jika tidak */
{
	if(IsEmpty(L)) return 0;
	if(Info(L) == X) return 1;
	return Search(Tail(L), X);
}



/*** Pencarian nilai ekstrim ***/
/* Prekondisi untuk Max/Min/Sum/Average : List tidak kosong */
infotype MaxList (List L)
/* Mengirimkan nilai info(P) yang maksimum */
{
	if(IsOneElmt(L)) return FirstElmt(L);
	return max(FirstElmt(L), MaxList(Tail(L)));
}

infotype MinList (List L)
/* Mengirimkan nilai info(P) yang minimum */
{
	if(IsOneElmt(L)) return FirstElmt(L);
	return min(FirstElmt(L), MinList(Tail(L)));	
}

infotype SumList (List L)
/* Mengirimkan total jumlah elemen List L */
{
	if(IsOneElmt(L)) return FirstElmt(L);
	return FirstElmt(L) + SumList(Tail(L));
}

float AverageList (List L)
/* Mengirimkan nilai rata-rata elemen list L */
{
	return (1.0f * SumList(L)) / NbElmtList(L);
}

/*** Operasi-Operasi Lain ***/
List InverseList (List L)
/* Mengirimkan list baru, hasil invers dari L dengan menyalin semua elemen list.
Semua elemen list baru harus dialokasi */
/* Jika alokasi gagal, hasilnya list kosong */
{
	if(IsOneElmt(L)) return Alokasi(FirstElmt(L));
	return KonsB(InverseList(Tail(L)), FirstElmt(L));
}

void SplitPosNeg (List L, List *L1, List *L2)
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */ 
/* L1 berisi semua elemen L yang positif atau 0, sedangkan L2 berisi
semua elemen L yang negatif; semua dengan urutan yang sama seperti di L */
/* L tidak berubah: Semua elemen L1 dan L2 harus dialokasi */
/* Jika L kosong, maka L1 dan L2 kosong */
{
	if(IsEmpty(L)) {
		*L1 = Nil; *L2 = Nil;
		return;
	}
	SplitPosNeg(Tail(L), L1, L2);
	if(FirstElmt(L) >= 0) *L1 = Konso(FirstElmt(L), *L1);
	else *L2 = Konso(FirstElmt(L), *L2);	
}

void SplitOnX (List L, infotype X, List *L1, List *L2)
/* I.S. L dan X terdefinisi, L1 dan L2 sembarang. */
/* F.S. L1 berisi semua elemen L yang lebih kecil dari X, dengan urutan
kemunculan yang sama, L2 berisi semua elemen L yang tidak masuk ke
L1, dengan urutan kemunculan yang sama. */
{
	if(IsEmpty(L)) {
		*L1 = Nil; *L2 = Nil;
		return;
	}
	SplitPosNeg(Tail(L), L1, L2);
	if(FirstElmt(L) < X) *L1 = Konso(FirstElmt(L), *L1);
	else *L2 = Konso(FirstElmt(L), *L2);
	
}

int ListCompare (List L1, List L2)
/* Menghasilkan: -1 jika L1 < L2, 0 jika L1 = L2, dan 1 jika L1 > L2 */
/* Jika L[i] adalah elemen L pada urutan ke-i dan |L| adalah panjang L: */
/* L1 = L2: |L1| = |L2| dan untuk semua i, L1[i] = L2[i] */
/* L1 < L2: Jika i adalah urutan elemen yang berbeda yang terkecil
dari L1 dan L2, L1[i]<L2[i] atau: Jika pada semua elemen pada
urutan i yang sama, L1[i]=L2[i], namun |L1|<|L2| */
/* Contoh: [3,5,6,7] < [4,4,5,6]; [1,2,3]<[1,2,3,4] */
/* L1>L2: kebalikan dari L1<L2 */
{
	if(IsEmpty(L1) && IsEmpty(L2)) return 0;
	if(IsEmpty(L1)) return -1;
	if(IsEmpty(L2)) return 1;
	
	if(FirstElmt(L1) != FirstElmt(L2)) return (FirstElmt(L1) > FirstElmt(L2))?1:-1;
	return ListCompare(Tail(L1), Tail(L2));
}

boolean IsAllExist (List L1, List L2)
/* Menghasilkan true jika semua elemen dalam L1 terdapat dalam L2 (tanpa
memperhatikan urutan ataupun banyaknya elemen).
Kedua list mungkin kosong. Jika L1 kosong, maka hasilnya false. */
{
	if(IsEmpty(L1)) return false;
	if(Search(L2, FirstElmt(L1))) IsEmpty(Tail(L1))?true:IsAllExist(Tail(L1), L2);
	return false;
}