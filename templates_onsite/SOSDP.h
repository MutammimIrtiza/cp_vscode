/**
 * Author: idk
 * Description: idk
 * Time: idk
 * Status: idk
 */
//  for problems like sum/count involving submaks/supermask,
//   we use sos dp to avoid overcounting.
//  x|y = x  :  y is submask of x
//  x&y = x  :  y is supermask of x
//  x&y = 0  :  y is submask of ~x

const int N=1<<20;
vll cnt(N);
vll dp1(N);
vll dp2(N);

void fwd1(vll& dp){ // dp[x] = cnt of submask of x
 L(bit,0,19){
  L(mask,0,N-1){
   if(getBit(mask,bit)) dp[mask]+=dp[resetbit(mask,bit)]; } } }

void bak1(vll& dp){ // return from submask count to mask count
 R(bit,19,0){
  R(mask,N-1,0){
   if(getBit(mask,bit)) dp[mask]-=dp[resetbit(mask,bit)]; } } }

void fwd2(vll& dp){ // dp[x] = cnt of supermask of x
 L(bit,0,19){
  R(mask,N-1,0){
   if(getBit(mask,bit)) dp[resetbit(mask,bit)]+=dp[mask]; } } }

void bak2(vll& dp){ // return from supermask count to mask count
 R(bit,19,0){
  L(mask,0,N-1){
   if(getBit(mask,bit)) dp[resetbit(mask,bit)]-=dp[mask]; } } }