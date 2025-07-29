# Student Attendance and Application Management System using AVL Tree

## Description

This project is a **student data management system** implemented in C, using an **AVL tree** for efficient storage, retrieval, and management of student records in a hierarchical manner. The system stores details such as student name, department, semester, roll number, subject marks, attendance, application status, and fee status, and is optimized for fast search, insertion, and deletion operations.

---

## Problem Statement

Managing large student databases, especially for academic and administrative purposes, requires quick and efficient access to records and the ability to perform frequent updates such as insertion and deletion while keeping the data balanced.

The primary problems solved by this project are:

- Efficient management and organization of student data by semester, department code, and roll number.
- Quick retrieval and modification of records without degradation in performance, achieved by maintaining the AVL tree balanced.
- Processing student attendance data, identifying maximum attendance in subjects (MCC), and calculating attendance percentages.
- Filtering students based on application status, attendance eligibility, fee payments, and identifying defaulters.
- Generating reports and segregated views of student data as required by administrative departments.

---

## Features

- Uses **AVL tree** to maintain balanced binary search tree structure for fast insertion, deletion, and search.
- Multi-key sorting: primary key by semester, second by department code, and third by roll number.
- Computes and stores subject-wise and overall attendance percentages dynamically.
- Filters students into categories such as:
  - Not applied for application
  - Eligible (application done + attendance > 74%)
  - Less attendance (< 75%)
  - Pending fee payment with sufficient attendance
  - Defaulters (less attendance or fee pending), with statistical insights on defaulter counts across departments
- Supports reading student data from a text file (`Input.txt`) for bulk loading.

---

## Data Model

Each student record (`Data_Gen`) contains:

- Name
- Department Code (`Dep_Code`)
- Semester (`sem`)
- Roll Number (`Roll_No`)
- Marks in 6 subjects (`Sub[6]`, where `Sub[5]` is MCC - most critical course)
- Attendance for 7 entries (`attendance[7]`), where `attendance[6]` is attendance percentage
- Application status (`application`: 0 or 1)
- Fee payment status (`fee_status`: 0 or 1)

---

## How It Works (High-Level)

- **Insertion and maintenance:** Data is stored in AVL tree nodes, where balancing operations (right rotation, left rotation) keep the tree height minimal.
- **Data insertion:** New student records are inserted based on semester, department code, and roll number.
- **Data processing:** The system identifies the subject with maximum marks (`mcc`), calculates attendance percentages, and updates the nodes accordingly.
- **Filtering:** Various functions traverse the AVL tree to create filtered subtrees based on set criteria (attendance, application status, fee status).
- **Reporting:** Prints in-order traversal of AVL tree, showing all student details in sorted order.

---

## How to Use

1. Prepare an `Input.txt` file with student data in the expected format (refer to the code's `make_tree` function for input reading structure):

   - Each record starts with a flag (`1` to insert, `0` to end).
   - Then input dependent fields: department code, semester, subject marks, name, roll number, attendance, application status, fee status.

2. Compile the C program:


3. Run the executable:

4. The output will show student records sorted by semester, department, and roll number, along with attendance and status details.

---

## Potential Improvements

- Add more detailed error handling for file I/O.
- Incorporate dynamic input from the user instead of just a file.
- Implement saving updated records back to file.
- Enhance filtering and reporting options based on additional criteria.
- Create user-friendly menus for interaction.

---

## Summary

This project demonstrates the practical use of AVL trees in managing complex student academic data with efficient sorting and querying capabilities. 
It automates common administrative tasks like attendance checking, fee status monitoring, and application processing, thereby aiding in better decision-making and student management.


