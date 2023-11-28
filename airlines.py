import sqlite3

conn = sqlite3.connect('airlines.db')
c = conn.cursor()
print("Opened database successfully")

conn.execute('''
CREATE TABLE IF NOT EXISTS AIRCRAFTS(
    CRAFT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
    MODEL TEXT NOT NULL,
    PASSENGERS INT NOT NULL,
    RANGE INT NOT NULL
);
''')

conn.execute('''
CREATE TABLE IF NOT EXISTS FLIGHTS (
    FLIGHT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
    CRAFT_ID INT NOT NULL,
    DEPARTURE TEXT NOT NULL,
    ARRIVAL TEXT NOT NULL,
    FOREIGN KEY (CRAFT_ID) REFERENCES AIRCRAFT(CRAFT_ID)
    );
''')

conn.execute('''
CREATE TABLE IF NOT EXISTS PILOTS (
    PILOT_ID INTEGER PRIMARY KEY AUTOINCREMENT,
    NAME TEXT NOT NULL,
    FLIGHT_ID INT NOT NULL,
    FOREIGN KEY (FLIGHT_ID) REFERENCES FLIGHTS(FLIGHT_ID)
    );
''')

conn.commit()

print("You can UPDATE, INSERT, DELETE, VIEW, etc. here")

def insert():
    table = input("Enter the table you want to insert into: ")
    if table == "AIRCRAFTS":
        model = input("Enter the model: ")
        passengers = input("Enter the number of passengers: ")
        range = input("Enter the range: ")
        c.execute("INSERT INTO AIRCRAFTS VALUES (?, ?, ?)", (model, passengers, range))
        conn.commit()
    elif table == "FLIGHTS":
        craft_id = input("Enter the craft ID: ")
        departure = input("Enter the departure: ")
        arrival = input("Enter the arrival: ")
        c.execute("INSERT INTO FLIGHTS VALUES (?, ?, ?)", (craft_id, departure, arrival))
        conn.commit()
    elif table == "PILOTS":
        name = input("Enter the name: ")
        flight_id = input("Enter the flight ID: ")
        c.execute("INSERT INTO PILOTS VALUES (?, ?)", (name, flight_id))
        conn.commit()
    else:
        print("Invalid table")

def view():
    table = input("Enter the table you want to view: ")
    c.execute("SELECT * FROM " + table)
    rows = c.fetchall()
    for row in rows:
        print(row)

def delete():
    table = input("Enter the table you want to delete from: ")
    if table == "AIRCRAFTS":
        craft_id = input("Enter the craft ID: ")
        c.execute("DELETE FROM AIRCRAFTS WHERE CRAFT_ID = ?", (craft_id,))
        conn.commit()
    elif table == "FLIGHTS":
        flight_id = input("Enter the flight ID: ")
        c.execute("DELETE FROM FLIGHTS WHERE FLIGHT_ID = ?", (flight_id,))
        conn.commit()
    elif table == "PILOTS":
        pilot_id = input("Enter the pilot ID: ")
        c.execute("DELETE FROM PILOTS WHERE PILOT_ID = ?", (pilot_id,))
        conn.commit()
    else:
        print("Invalid table")

command = input("Enter your command: ")

if command == "UPDATE":
    # Update the database
    pass
elif command == "INSERT":
    insert()
elif command == "DELETE":
    # Delete from the database
    pass
elif command == "VIEW":
    view()
else:
    print("Invalid command")

