/*
You are given N particles, each characterized by a charge value – Aᵢ.
Every pair of particles interacts with each other.
The value of the interaction, regardless of the charge values of the particles, is at least K.
If the absolute difference between the charges of two particles is greater than K, the interaction between those particles is equal to that number.
Your task is to calculate the sum of the interaction values between all pairs of particles.

Input
The first line of standard input contains two integers N and K
(1 ≤ N ≤ 10⁶; 1 ≤ K ≤ 10⁴).
The second line contains N integers Aᵢ (1 ≤ Aᵢ ≤ 10⁴)

Output
The only line of standard output should contain the required number – the sum of the interaction values between all pairs of particles.

Examples:
Input: 
4 3
1 2 4 5

Output:
19

Input: 
3 9
10 19 1

Output:
36

Input:
5 1
6 6 9 1 2

Output:
41

Explanation for the First Example:
The interaction between all pairs of particles is 3, except for the particles with charge values 1 and 5 – in that case, the interaction is 4. The result is therefore calculated as:
5 × 3 + 4 = 19.
*/

#include<iostream>
#include<algorithm>
using namespace std;

const int limit1 = 1e6 + 7, limit2 = 1e4 + 4;
long long arr[limit1]; // array of charges (or particles)
long long prefixSum[limit1]; // prefix sum of the sorted array
long long countArray[limit2]; // prefix sum of the count array

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    long long n, k;
    cin >> n >> k; // input number of particles (n) and the minimum interaction (k)
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // input the charge values
    }
    sort(arr, arr + n + 1); // sorting the array of charges

    long long result = 0; // to store the final result
    int lastPos = 0; // last processed position in the count array
    for (int i = 1; i <= n; i++) {

        prefixSum[i] = prefixSum[i - 1] + arr[i]; 
        for (int j = lastPos + 1; j <= arr[i]; j++) {
            countArray[j] = countArray[j - 1]; 
        }
        lastPos = arr[i];

        long long temp = countArray[arr[i]] - countArray[max(arr[i] - k - 1, 0LL)]; // difference <= k
        result += temp * k; 
        result += arr[i] * (i - 1 - temp) - prefixSum[i - 1 - temp];

        countArray[arr[i]]++; 
    }

    cout << result; // output the final result
}
