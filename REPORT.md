# CSC-531 Lab 01 - Student Report

**Roll No.:*68* 
**Student name:*Ayman abbasi* 
**Section (A/B):*B* 
**GitHub username:*abbasiayman96* 

## 1. Aim and input assumptions

Aim of this lab is to understand how arrays work in memory and how insertion and deletion work by shifting elements.

Relationship:
- Capacity = total slots reserved in array, here 8.
- Logical size = number of active elements, here 4.
- Active indices = 0 to size-1, so 0 to 3.


Input assumptions: Initial array = [70, 80, 90, 85], size = 4, capacity = 8.

## 2. Task A - Array diagram and address calculations

### Array Diagram
Capacity = 8, Logical size = 4

| Index | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
|---|---|---|---|---|---|---|---|---|
| Value | 70 | 80 | 90 | 85 | - | - | - | - |
| Status | Active | Active | Active | Active | Free | Free | Free | Free |

- Active Items: Index 0 to 3
- Free Slots: Index 4 to 7
- Next Append Index: 4

### 1D Address Worksheet
Formula: Address(A[i]) = B + i * w
Given: B = 4000, w = 4

- A[0] = 4000 + 0 * 4 = 4000
- A[3] = 4000 + 3 * 4 = 4000 + 12 = 4012
- A[7] = 4000 + 7 * 4 = 4000 + 28 = 4028

### 2D Row-Major Worksheet
Given: M[4][5], B = 2000, w = 4, Find M[2][3]

Formula: Address = B + (i * total_columns + j) * w

- Linear Offset = 2 * 5 + 3 = 10 + 3 = 13
- Address M[2][3] = 2000 + 13 * 4 = 2000 + 52 = 2052

Why multiplied by element width? Because each element takes 4 bytes. Offset tells how many elements to skip, so we multiply by 4 to get total bytes to skip.

## 3. Task B - Insertion / deletion trace

Initial active values: [70, 80, 90, 85], size = 4, capacity = 8

### Insertion of 75 at index 2

- Shift: a[4] = a[3] = 85
- Shift: a[3] = a[2] = 90
- Insert: a[2] = 75
- Final array: [70, 80, 75, 90, 85]
- Final logical size: 5

### Deletion of element at index 1 from updated array

Updated array before deletion: [70, 80, 75, 90, 85]

- Delete element at index 1, which is 80
- Shift: a[1] = a[2] = 75
- Shift: a[2] = a[3] = 90
- Shift: a[3] = a[4] = 85
- Resulting active values: [70, 75, 90, 85]
- Final logical size: 4

## 4. Task C - Menu demonstration

Menu Options:
1. Insert element
2. Delete element
3. Display array
4. Exit

Enter choice: 1
Enter position and value: 2 75
Inserted successfully.
Array: [70, 80, 75, 90, 85]

### Failed Cases

1. Failed Insertion at Full Capacity:
   Size = 8, Capacity = 8
Enter choice: 1
Enter position and value: 8 100
Insertion failed: Array is full.

2. Failed Deletion from Empty List:
   Size = 0
Enter choice: 2
Enter position: 0
Deletion failed: List is empty.

###validation test table 
| # | Test | Input / Action | Expected | Observed | Result |
|---|---|---|---|---|---|
| 1 | Insert in middle | [70, 80, 90, 85], insert 75 at 2 | [70, 80, 75, 90, 85], size 5 | [70, 80, 75, 90, 85], size 5 | Pass |
| 2 | Delete first | [70, 80, 90, 85], delete at 0 | [80, 90, 85], size 3 | [80, 90, 85], size 3 | Pass |
| 3 | Delete middle | [70, 80, 75, 90, 85], delete at 2 | [70, 80, 90, 85], size 4 | [70, 80, 90, 85], size 4 | Pass |
| 4 | Delete last | [70, 80, 90, 85], delete at 3 | [70, 80, 90], size 3 | [70, 80, 90], size 3 | Pass |
| 5 | Insert when full | Size 8, Capacity 8, insert 100 | Insertion failed | Insertion failed | Pass |
| 6 | Delete when empty | Size 0, delete at 0 | Deletion failed | Deletion failed | Pass |
| 7 | Invalid negative index | Insert at -1 | Insertion failed | Insertion failed | Pass |
| 8 | Invalid index == size for delete | Size 4, delete at 4 | Deletion failed | Deletion failed | Pass |

###complexity and limitations

| Operation   | Shifts       | Worst Case     | Space |
| Insert      | n - p        | O(n)           | O(1) |
| Delete      | n - p - 1    | O(n)           | O(1) |

Insertion: Elements from p to n are shifted one step to the right.
Deletion: Elements from p+1 to n are shifted one step to the left.
Worst case occurs at p = 1.Assumptions and Restrictions:Elements are stored in a contiguous array.p is valid. For insertion 1 <= p <= n+1, for deletion 1 <= p <= n.Array has enough capacity for insertion.Shifting is done in-place, no extra array is required.
##Reflection and viva preparation

how many shifts are required to insert at position p into an active list of n elements?

Answer: n - p + 1 shifts are required. Elements from p to n are shifted one step to the right to create space for the new element.

Why does insertion shift backward while deletion shifts forward?

Answer: Insertion shifts backward (from n down to p) so that no element is overwritten before it is moved. Deletion shifts forward (from p+1 up to n) because the gap is at p and each next element is moved into the previous empty position.

Which workload favors arrays: frequent indexed access or frequent front insertion? Explain.

Answer: Frequent indexed access favors arrays. Arrays give O(1) access by index because elements are stored in contiguous memory. Frequent front insertion does not favor arrays because every insertion at the front requires O(n) shifts.

**One bug I encountered:** Off-by-one error in the shifting loop, the last element was overwritten.
**How I detected it:** When inserting at p = 1, the last element was lost in the output.
**What I changed:** Changed the loop to start from n and go down to p, and updated size after shifting.
**External/AI assistance disclosed, if applicable:** AI assistance was used for explanation and formatting.
