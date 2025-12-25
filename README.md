# 🏥 IntelliCare – Smart Hospital Information System

**Team Name:** GeekyCoders
**Problem Statement:** PS03 – Hospital Information System
**Hackathon:** Quasar 4.0
**College:** Shah & Anchor Kutchhi Engineering College

---

## 🔹 Project Overview

**IntelliCare** is a **unified Hospital Information System (HIS)** that digitizes core OPD/IPD workflows and provides hospitals with a **real-time 360° operational view** of patients, appointments, rooms, and departments.

The system reduces manual work, removes departmental gaps, and improves emergency response using **data-structure-driven logic** and a **web-based dashboard**.

---

## 🔹 Design Philosophy

The project was built in **two phases**:

### Phase 1 – Algorithm & Logic Design

* Implemented using **C (DSAA)**
* Focused on correctness and efficiency
* Data Structures used:

  * Linked List → Patient records
  * Priority Queue → Appointment scheduling
  * Graph + BFS → Department navigation

### Phase 2 – Production-Style HIS

* Same logic scaled into a real system
* Backend APIs using **Python Flask**
* Database using **MySQL (XAMPP)**
* Web dashboard using **HTML, CSS, Bootstrap**

This approach ensures **algorithmic depth + real-world usability**.

---

## 🔹 Key Features (PS03 Aligned)

* Centralized patient registration
* Priority-based appointment scheduling (emergency-first)
* OPD + IPD workflow support
* Room allocation and vacating
* Real-time dashboard statistics
* Department navigation using **BFS (Graph traversal)**
* Modular and analytics-ready architecture

---

## 🔹 Technology Stack

**Core Logic**

* C Programming
* Data Structures & Algorithms

**Backend**

* Python Flask
* REST APIs

**Database**

* MySQL (XAMPP)

**Frontend**

* HTML
* CSS
* Bootstrap

**Architecture**

* API-driven
* Modular
* Scalable

---

## 🔹 System Requirements (For Judges)

* Python 3.9 or higher
* XAMPP (Apache + MySQL)
* Any modern web browser
* No internet required during demo

---

## 🔹 Project Structure

```
IntelliCare/
│
├── app.py                     # Flask backend (APIs + BFS logic)
├── templates/
│   └── index.html              # Dashboard UI
├── intellicare_his.sql         # Complete database setup
├── README.md                   # This file
└── c_prototype/ (optional)     # DSAA logic in C (Phase 1)
```

---

## 🔹 Database Setup (One-Time)

1. Start **XAMPP**

   * Start **Apache**
   * Start **MySQL**

2. Open browser:

   ```
   http://localhost/phpmyadmin
   ```

3. Click **Import**

4. Upload:

   ```
   intellicare_his.sql
   ```

5. Click **Go**

✔ Database
✔ Tables
✔ Departments
✔ Rooms
✔ BFS graph
✔ Sample data

All created automatically.

---

## 🔹 How to Run the System

### Step 1: Start Backend

Open terminal in project folder:

```bash
python app.py
```

Expected output:

```
Running on http://127.0.0.1:5000
```

---

### Step 2: Open Dashboard

Open browser and visit:

```
http://127.0.0.1:5000/
```

---

## 🔹 How Judges Can Test the System (Demo Flow)

### 1️⃣ Patient Registration

* Use **Add Patient**
* Enter details and save
* Patient appears in Patients table instantly

✔ Tests patient digitization

---

### 2️⃣ Appointment Scheduling (Priority Queue)

* Schedule appointment
* Assign department and priority (1 = emergency)
* Queue auto-orders by priority

✔ Tests emergency-first logic

---

### 3️⃣ Appointment Queue & Next Appointment

* View sorted appointment queue
* Observe **Next Appointment** panel

✔ Tests real-time scheduling

---

### 4️⃣ Room Allocation (IPD)

* Assign room to patient
* Room becomes occupied
* Vacate room to free it

✔ Tests IPD management

---

### 5️⃣ Department Navigation (Graph + BFS)

* Select starting department
* Run BFS
* Traversal path is displayed visually

✔ Tests graph-based navigation

---

### 6️⃣ System Snapshot (360° View)

Dashboard shows:

* Total patients
* Pending appointments
* Occupied rooms
* Live updates using **Refresh All**

✔ Tests real-time hospital visibility

---

## 🔹 Why This Solves PS03

* Unified Hospital Information System
* Digitizes OPD/IPD workflows
* Provides real-time operational data
* Reduces manual work and departmental gaps
* Scalable and modular for future hospital needs

---

## 🔹 Demo Explanation 

> “We first designed the hospital workflow logic using C and data structures to ensure correctness.
> After validating the logic, we scaled it into a real-time Hospital Information System using Flask, MySQL, and a dashboard.
> This ensures both strong algorithmic design and practical usability.”

---

## 🔹 Conclusion

**IntelliCare** demonstrates how core **computer science fundamentals** can be transformed into a **deployable, real-world Hospital Information System**, fully aligned with PS03 objectives.

---
