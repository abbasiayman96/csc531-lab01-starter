# Lab 01 Report — Arrays, Address Calculations and Safe Insertion/Deletion

- *Roll Number:* 68

## Task A — Representation and Address Worksheet

### 1. Indexed 8-Slot Array (Capacity = 8, Logical Size = 4)

Index:   [ 0 ]  [ 1 ]  [ 2 ]  [ 3 ]  [ 4 ]  [ 5 ]  [ 6 ]  [ 7 ]
Value:   [ 10 ] [ 20 ] [ 30 ] [ 40 ] [  - ] [  - ] [  - ] [  - ]
Status:   ACT    ACT    ACT    ACT    UNU    UNU    UNU    UNU
                                       ^
                              Next append index = 4

- Active positions (logical size = 4): Indices 0, 1, 2, 3 (containing active elements).
- Unused slots (4 remaining capacity): Indices 4, 5, 6, 7 (8 - 4 = 4 unused slots).
- Next append position: Index 4 (equal to logical size).

### 2. One-Dimensional Array Address Calculations

Given hypothetical base address B = 4000 and element width w = 4 (assuming hypothetical worksheet width w = 4; actual byte size of int is platform-dependent via sizeof(int)):[span_3](start_span)[span_3](end_span)

Formula: Addr(A[i]) = B + i * w

- For A[0]: Addr(A[0]) = 4000 + (0 * 4) = 4000[span_4](start_span)[span_4](end_span)[span_5](start_span)[span_5](end_span)
- For A[3]: Addr(A[3]) = 4000 + (3 * 4) = 4000 + 12 = 4012[span_6](start_span)[span_6](end_span)[span_7](start_span)[span_7](end_span)
- For A[7]: Addr(A[7]) = 4000 + (7 * 4) = 4000 + 28 = 4028[span_8](start_span)[span_8](end_span)[span_9](start_span)[span_9](end_span)

### 3. Row-Major 2D Array Address Calculation (M[4][5])

Given row-major matrix M[4][5] (4 rows, 5 columns), hypothetical base address B = 2000, and element width w = 4:[span_10](start_span)[span_10](end_span)[span_11](start_span)[span_11](end_span)

In row-major order, each complete row has 5 elements. Reaching M[2][3] skips 2 full rows (2 * 5 = 10 elements) plus 3 elements in row 2, giving a total offset of 13 elements (13 * 4 = 52 bytes).[span_12](start_span)[span_12](end_span)[span_13](start_span)[span_13](end_span)

Formula: Addr(M[r][c]) = B + ((r * cols + c) * w)[span_14](start_span)[span_14](end_span)[span_15](start_span)[span_15](end_span)
Calculation: Addr(M[2][3]) = 2000 + ((2 * 5 + 3) * 4) = 2000 + (13 * 4) = 2000 + 52 = 2052[span_16](start_span)[span_16](end_span)[span_17](start_span)[span_17](end_span)

## Task B & C — Implementation Summary

- Implemented insertAt() and deleteAt() in lab01.cpp using fixed-array shifting without STL vectors or STL insertion/deletion helpers, keeping lab01.hpp unchanged.[span_18](start_span)[span_18](end_span)[span_19](start_span)[span_19](end_span)
- Implemented main.cpp with the 4-option menu (Display, Insert, Delete, Exit), tracking logical size separately from capacity, and demonstrating normal operations, full-array insertion rejection, and empty-array deletion rejection.[span_20](start_span)[span_20](end_span)[span_21](start_span)[span_21](end_span)

## Tracing, Testing, and Analysis

### 1. Step-by-Step Annotated Trace

#### Insertion Trace: insertAt(a, size, cap, 1, 15) on [10, 20, 30], size = 3, cap = 5
1. Validate cap, size, and pos (0 <= 1 <= 3 and size < cap) -> valid.[span_22](start_span)[span_22](end_span)[span_23](start_span)[span_23](end_span)
2. Shift a[2] (30) to index 3 -> [10, 20, 30, 30], size = 3.[span_24](start_span)[span_24](end_span)
3. Shift a[1] (20) to index 2 -> [10, 20, 20, 30], size = 3.[span_25](start_span)[span_25](end_span)
4. Write 15 at index 1 -> [10, 15, 20, 30], size = 3.[span_26](start_span)[span_26](end_span)
5. Increment logical size from 3 to 4 -> active array [10, 15, 20, 30], size = 4.[span_27](start_span)[span_27](end_span)

#### Deletion Trace: deleteAt(a, size, 2) on [10, 15, 20, 30], size = 4
1. Validate non-empty array and index 2 (0 <= 2 < 4) -> valid.[span_28](start_span)[span_28](end_span)[span_29](start_span)[span_29](end_span)
2. Shift a[3] (30) to index 2 -> [10, 15, 30, 30], size = 4.[span_30](start_span)[span_30](end_span)
3. Decrement logical size from 4 to 3 -> active array [10, 15, 30], size = 3 (stale value in unused slot is ignored).[span_31](start_span)[span_31](end_span)

### 2. Expected vs. Actual Test Table

| Scenario | Expected Result | Actual Result |
| :--- | :--- | :--- |
| Insert at beginning (pos 0) | Value placed at index 0, remaining shifted right, size + 1, returns true | Pass: shifted right and size incremented |
| Insert in middle | Elements from pos onward shift right, value inserted, size + 1, returns true | Pass: shifted right and size incremented |
| Insert at end (pos = size) | Appended at logical size index, size + 1, returns true | Pass: appended and size incremented |
| Delete first element (pos 0) | Elements shift left, size - 1, returns true | Pass: shifted left and size decremented |
| Delete middle element | Following elements shift left, size - 1, returns true | Pass: shifted left and size decremented |
| Delete last element | Logical size decreases by 1, returns true | Pass: size decremented |
| Full array insert | Returns false; array contents and logical size unchanged | Pass: rejected before shifting |
| Invalid index (insert/delete) | Returns false; array contents and logical size unchanged | Pass: rejected by bounds check |
| Empty array delete | Returns false; array contents and logical size unchanged | Pass: rejected before shifting |
| Repeated operations | Sequence of valid inserts/deletes maintains valid contents and size | Pass: state remains consistent |

### 3. Time and Auxiliary Space Analysis

- insertAt(): Best case O(1) (insert at end without shifting), worst case O(n) (insert at index 0 shifting n elements), auxiliary space O(1).[span_32](start_span)[span_32](end_span)
- deleteAt(): Best case O(1) (delete last element without shifting), worst case O(n) (delete at index 0 shifting n - 1 elements), auxiliary space O(1).[span_33](start_span)[span_33](end_span)

### 4. Bug Corrected

- Bug: Checking/shifting without full validation before modifying elements or reading past active bounds during shifts could corrupt array state or out-of-range indices.[span_34](start_span)[span_34](end_span)[span_35](start_span)[span_35](end_span)
- Fix: Validated capacity, logical size, and index bounds upfront before shifting or mutating size, keeping failed operations completely unchanged.[span_36](start_span)[span_36](end_span)[span_37](start_span)[span_37](end_span)

### 5. Reflections

1. Why distinguish logical size from array capacity?
   Capacity is total allocated slots, while logical size is active elements currently stored; separating them tracks where to append, detects full state, and avoids reading unused slots.[span_38](start_span)[span_38](end_span)[span_39](start_span)[span_39](end_span)[span_40](start_span)[span_40](end_span)

2. Why shift elements instead of overwriting or leaving gaps?
   Contiguous arrays depend on dense indices 0..size-1; shifting preserves order on insertion and closes gaps on deletion without losing active elements.[span_41](start_span)[span_41](end_span)[span_42](start_span)[span_42](end_span)

3. How do boundary checks protect program correctness?
   Checking bounds and capacity before writing or shifting prevents out-of-range access, undefined behavior, and partial updates on invalid calls.[span_43](start_span)[span_43](end_span)[span_44](start_span)[span_44](end_span)
