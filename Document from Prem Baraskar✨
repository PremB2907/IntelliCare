from flask import Flask, request, jsonify, render_template
import mysql.connector

# ---------- FLASK APP SETUP ----------
app = Flask(__name__, template_folder="templates")


# ---------- DB CONNECTION (XAMPP MySQL) ----------
def get_connection():
    conn = mysql.connector.connect(
        host="localhost",
        user="root",          # XAMPP default user
        password="",          # put password here if you set one
        database="intellicare_his"   # your DB name
    )
    return conn


# ---------- ROUTE: DASHBOARD PAGE ----------
@app.route("/")
def index():
    return render_template("index.html")


# ---------- PATIENT ROUTES ----------

@app.route("/patients", methods=["GET"])
def get_patients():
    conn = get_connection()
    cursor = conn.cursor(dictionary=True)
    cursor.execute("SELECT * FROM patients")
    rows = cursor.fetchall()
    cursor.close()
    conn.close()
    return jsonify(rows)


@app.route("/patients", methods=["POST"])
def add_patient():
    data = request.json
    conn = get_connection()
    cursor = conn.cursor()
    sql = """
        INSERT INTO patients (patient_id, name, age, gender, diagnosis)
        VALUES (%s, %s, %s, %s, %s)
    """
    vals = (
        data["patient_id"],
        data["name"],
        data["age"],
        data["gender"],
        data.get("diagnosis", "")
    )
    cursor.execute(sql, vals)
    conn.commit()
    cursor.close()
    conn.close()
    return jsonify({"message": "Patient added"}), 201


# ---------- APPOINTMENT ROUTES ----------

@app.route("/appointments", methods=["GET"])
def get_appointments():
    conn = get_connection()
    cursor = conn.cursor(dictionary=True)
    sql = """
        SELECT a.id, a.patient_id, p.name AS patient_name,
               d.name AS department_name, a.priority, a.status, a.created_at
        FROM appointments a
        JOIN patients p ON a.patient_id = p.patient_id
        JOIN departments d ON a.department_id = d.id
        ORDER BY a.priority ASC, a.created_at ASC
    """
    cursor.execute(sql)
    rows = cursor.fetchall()
    cursor.close()
    conn.close()
    return jsonify(rows)


@app.route("/appointments", methods=["POST"])
def add_appointment():
    data = request.json
    conn = get_connection()
    cursor = conn.cursor()
    sql = """
        INSERT INTO appointments (patient_id, department_id, priority)
        VALUES (%s, %s, %s)
    """
    vals = (
        data["patient_id"],
        data["department_id"],
        data["priority"]
    )
    cursor.execute(sql, vals)
    conn.commit()
    cursor.close()
    conn.close()
    return jsonify({"message": "Appointment added"}), 201


@app.route("/appointments/next", methods=["GET"])
def get_next_appointment():
    conn = get_connection()
    cursor = conn.cursor(dictionary=True)
    sql = """
        SELECT a.id, a.patient_id, p.name AS patient_name,
               d.name AS department_name, a.priority, a.status, a.created_at
        FROM appointments a
        JOIN patients p ON a.patient_id = p.patient_id
        JOIN departments d ON a.department_id = d.id
        WHERE a.status = 'scheduled'
        ORDER BY a.priority ASC, a.created_at ASC
        LIMIT 1
    """
    cursor.execute(sql)
    row = cursor.fetchone()
    cursor.close()
    conn.close()
    if row:
        return jsonify(row)
    return jsonify({"message": "No appointments"}), 404


# ---------- ROOM ROUTES ----------

@app.route("/rooms", methods=["GET"])
def get_rooms():
    conn = get_connection()
    cursor = conn.cursor(dictionary=True)
    cursor.execute("SELECT * FROM rooms ORDER BY room_number ASC")
    rows = cursor.fetchall()
    cursor.close()
    conn.close()
    return jsonify(rows)


# ---------- MAIN ----------
if __name__ == "__main__":
    app.run(debug=True)
