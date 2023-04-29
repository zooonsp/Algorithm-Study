/*
  Croatia 2005 / National Competition #2 / Seniors
  Problem LABUDOVI
  (문제 백조)

  Simuliramo otapanje leda, dan po dan, i izmedju svaka dva otapanja
  (우리는 날마다, 그리고 두 번 녹는 사이에 얼음이 녹는 것을 시뮬레이션합니다.)
  provjeravamo moze li jedan labud doci do drugoga.
  (provjeravamo moze li jedan labud doci do drugoga.)

  Za otapanje leda i pretrazivanje svih polja do kojih moze jedan labud doci
  koristimo strukturu red (queue) i to 2 queuea za otapanje i jos 2 queuea za
  pretrazivanje kako bi osigurali da svako polje najvise jedanput otopimo i pretrazimo.
  (얼음을 녹이고 백조 한 마리가 도달할 수 있는 모든 필드를 검색하기 위해 
  각 필드를 최대 한 번 녹이고 검색하도록 하기 위해 
  2개의 녹는 큐와 2개의 추가 검색 큐라는 큐 구조를 사용합니다.)

  Dakle, ukupna vremenska slozenost je O(R*S).
  (따라서 총 시간 복잡도는 O(R*S)입니다.)
*/

#include <cstdio>
#include <queue>

using namespace std;

int R, S;
struct coords {
   short r, s;
   coords() {}
   coords( int rr, int ss ) { r = rr; s = ss; }
   int ok() { return r >= 0 && r < R && s >= 0 && s < S; }
   friend coords operator + ( const coords &a, const coords &b ) {
      return coords( a.r + b.r, a.s + b.s );
   }
};

coords labud1, labud2; // 크로아티아어 백조
char bio[1500][1500]; // 백조가 갈 수 있는 길 표시하는 용도
char otopio[1500][1500]; // 크로아티아어 녹은 것
char jezero[1500][1501]; // 크로아티아어 호수

// danas : 오늘, sutra : 내일
queue<coords> labud_danas, labud_sutra;
queue<coords> otopi_danas, otopi_sutra;

int main( void ) {
   scanf( "%d%d", &R, &S );

   int broj = 0; // 크로아티아어 숫자
   for( int r = 0; r < R; ++r ) {
      scanf( "%s", jezero[r] );
      for( int s = 0; s < S; ++s ) {
         if( jezero[r][s] == 'L' ) {
            if( ++broj == 1 ) labud1 = coords( r, s );
            else              labud2 = coords( r, s );
            jezero[r][s] = '.';
         }
         if( jezero[r][s] == '.' ) { otopio[r][s] = 1; otopi_sutra.push( coords( r, s ) ); }
      }
   }

   const coords delta[4] = { coords( -1, 0 ), coords( 0, 1 ), coords( 1, 0 ), coords( 0, -1 ) };

   labud_sutra.push( labud1 );
   bio[labud1.r][labud1.s] = 1;

   int dan; // 낮
   for( dan = 0; !bio[labud2.r][labud2.s]; ++dan ) {

      // premjesti sutra u danas... dosao je novi dan (내일을 오늘로 옮겨라... 새로운 날이 왔다)
      for( ; !labud_sutra.empty(); labud_sutra.pop() ) labud_danas.push( labud_sutra.front() );
      for( ; !otopi_sutra.empty(); otopi_sutra.pop() ) otopi_danas.push( otopi_sutra.front() );

      // otopi danas i nadji sto ce se sutra otopit (오늘 녹는 얼음 갱신)
      for( ; !otopi_danas.empty(); otopi_danas.pop() ) {
         coords a = otopi_danas.front();
         jezero[a.r][a.s] = '.';
         for( int d = 0; d < 4; ++d ) {
            coords b = a+delta[d];
            if( !b.ok() || otopio[b.r][b.s] ) continue; // 범위 밖 or 이미 녹은 얼음

            otopio[b.r][b.s] = 1;
            otopi_sutra.push( b );
         }
      }

      // istrazi nova polja u koja moze labud1 doci (백조가 올 수 있는 새로운 길 탐험)
      for( ; !labud_danas.empty(); labud_danas.pop() ) {
         coords a = labud_danas.front();
         for( int d = 0; d < 4; ++d ) {
            coords b = a+delta[d];
            if( !b.ok() || bio[b.r][b.s] ) continue; // 범위 밖 or 이미 감

            bio[b.r][b.s] = 1;
            if( jezero[b.r][b.s] == '.' ) labud_danas.push( b ); // 이미 녹아 있는 얼음
            if( jezero[b.r][b.s] == 'X' ) labud_sutra.push( b ); // 내일 녹을 예정인 얼음
         }
      }
   }

   printf( "%d\n", dan-1 );

   return 0;
}
