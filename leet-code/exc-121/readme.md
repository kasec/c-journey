121. Best Time to Buy and Sell Stock

You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

 

Example 1:

Input: prices = [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Note that buying on day 2 and selling on day 1 is not allowed because you must buy before you sell.
Example 2:

Input: prices = [7,6,4,3,1]
Output: 0
Explanation: In this case, no transactions are done and the max profit = 0.

[2,4,3,1] => 2
[3,3,2,5,7] => 3

highest = 0;
lowest = 1000;

---
current = 3;
lowest is 3 because is minor than 1000;
highest profit is 0, becasue current - lowest is 0
---
current = 3;
lowest is still 3 because current is not minor
highest is still 0, because current - lowest is still 0;
---
current = 2;
lowest is 2 because current is minor than lowest previous value
highest is 0 because lowest - current is 0
---
current = 5;
lowest is still 2, you know right?
highest is 3, lowest(2) - current(5)
---
current = 7
lowest is still 2,
highest is 5, lowest(2) - current(7)




Constraints:

1 <= prices.length <= 105
0 <= prices[i] <= 104

# Pseudo solution

I need to figure out how to get revenue, based on a list

Get the lowest value
If this is the last postion, return 0
If not, get the highest of the remaining list

[EDIT]

Seems my las algorithm is not fully working some use cases failed, however I know how to fix it.

I need to get diference between 2 values and, biggest difference will be returned

I finished, yeah, i took me 3 iterations and had to see an explination for it.