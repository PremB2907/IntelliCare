# 🏥 IntelliCare – Smart Hospital Information System

**Team:** GeekyCoders
**Problem Statement:** PS03 – Hospital Information System
**Hackathon:** Quasar 4.0

---

## 🔹 Overview

IntelliCare is a **unified Hospital Information System (HIS)** that digitizes core OPD/IPD workflows and provides a **real-time dashboard** for managing patients, appointments, rooms, and departments.

The system is designed in two phases:

* **Phase 1:** Core logic using Data Structures in C (DSAA prototype)
* **Phase 2:** Scaled, production-style web system using Flask + MySQL + Dashboard

---

## 🔹 System Requirements (Judge Side)

Minimum requirements to test the system:

* Windows / Linux / macOS
* **Python 3.9+**
* **XAMPP** (Apache + MySQL)
* Web browser (Chrome / Edge)

> ⚠️ No internet required during demo (all local).

---

## 🔹 Project Structure

```
IntelliCare/
│
├── app.py                     # Flask backend (APIs + BFS logic)
├── templates/
│   └── index.html              # Dashboard UI
├── README.md                   # This file
└── (optional) c_prototype/     # DSAA C-based logic (Phase 1)
```

---

## 🔹 Database Setup (One-Time)

1. Start **XAMPP**

   * Start **Apache**
   * Start **MySQL**

2. Open browser →
   `http://localhost/phpmyadmin`

3. Create database:

   ```
   intellicare_his
   ```

4. Required tables:

   * `patients`
   * `appointments`
   * `rooms`
   * `departments`
   * `department_edges`

*(Tables are created using SQL scripts provided in documentation / setup notes.)*

5. Insert:

   * Departments (Emergency, Cardiology, Radiology, etc.)
   * Rooms (e.g., room numbers 101–120, occupied = 0)
   * Department graph edges (for BFS navigation)

---

## 🔹 How to Run the System (Judges)

### Step 1: Start Backend

Open terminal in project folder and run:

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

The **IntelliCare Dashboard** will load.

---

## 🔹 How Judges Can Test Features (Demo Flow)

### ✅ 1. Patient Registration

* Go to **Add Patient**
* Enter Patient ID, Name, Age, Gender, Diagnosis
* Click **Save Patient**
* Patient appears instantly in **Patients Table**

✔ Tests patient record digitization

---

### ✅ 2. Appointment Scheduling (Priority Queue)

* Go to **Schedule Appointment**
* Enter Patient ID
* Enter Department ID
* Set Priority (1 = Emergency, 5 = Normal)
* Click **Add Appointment**

✔ Appointments auto-sorted by **priority + time**

---

### ✅ 3. Real-Time Appointment Queue

* Scroll to **Appointment Queue**
* Observe priority badges (High / Medium / Low)
* Check **Next Appointment** panel

✔ Demonstrates emergency-first logic

---

### ✅ 4. Room Allocation (IPD)

* Enter Patient ID → click **Assign Room**

* First available room is allocated

* Room status updates instantly

* Enter Room Number → click **Vacate**

* Room becomes free

✔ Tests IPD room management

---

### ✅ 5. Department Navigation (Graph + BFS)

* Select a department from dropdown
* Click **Run BFS**
* BFS traversal path is displayed visually

✔ Demonstrates graph traversal for hospital navigation

---

### ✅ 6. System Snapshot (360° View)

Dashboard displays:

* Total patients
* Pending appointments
* Occupied rooms
* Live updates via **Refresh All**

✔ Real-time hospital visibility

---

## 🔹 Technology Stack

**Core Logic (Phase 1):**

* C Programming
* Data Structures:

  * Linked List
  * Priority Queue
  * Graph (BFS)

**Production System (Phase 2):**

* Backend: **Python Flask**
* Database: **MySQL (XAMPP)**
* Frontend: **HTML, CSS, Bootstrap**
* Architecture: REST APIs + Dashboard

---

## 🔹 Why This Solves PS03

* ✔ Unified Hospital Information System
* ✔ Digitizes OPD/IPD workflows
* ✔ Real-time 360° view of patients & resources
* ✔ Reduces manual work & departmental gaps
* ✔ Scalable, modular, analytics-ready

---

## 🔹 Demo Tip for Judges (You Can Say This)

> “We first designed the hospital logic using C and data structures.
> Once validated, we scaled the same logic into a real-time Hospital Information System using Flask, MySQL, and a dashboard.
> This ensures both algorithmic correctness and real-world usability.”

---

## 🔹 Conclusion

IntelliCare demonstrates how **data structures + system design** can be transformed into a **practical, deployable Hospital Information System**, fully aligned with PS03 requirements.

