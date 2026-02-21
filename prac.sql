DECLARE 
    ENAME VARCHAR2(100); -- BRACKET, SEMICOLON
BEGIN   
    SELECT (FIRST_NAME || LAST_NAME) INTO ENAME
    FROM EMPLOYEES
    WHERE EMPLOYEE_ID = 100;
    DBMS_OUTPUT.PUT_LINE('The name is : ' || ENAME); 
END;
/
SHOW ERRORS;



DECLARE 
    HDATE DATE;
    YEARS NUMBER;
BEGIN
    SELECT HIRE_DATE INTO HDATE
    FROM EMPLOYEES
    WHERE EMPLOYEE_ID = 100000;
    YEARS := (MONTHS_BETWEEN(SYSDATE, HDATE)/12);
    
    IF YEARS >= 10 THEN
        DBMS_OUTPUT.PUT_LINE('The employee worked : ' || YEARS || ' years');
    ELSE 
        DBMS_OUTPUT.PUT_LINE('');
    END IF;

EXCEPTION 
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('Not found');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('');
    
END;
/



SELECT TO_NUMBER('100') + 50 FROM DUAL;
/



DECLARE 
    YRS NUMBER;
    CNT NUMBER;
BEGIN
    CNT := 0;
    FOR R IN (SELECT HIRE_DATE FROM EMPLOYEES)
    LOOP    
        YRS := ((MONTHS_BETWEEN(SYSDATE, R.HIRE_DATE))/12);
        IF YRS >= 10 THEN
            CNT := CNT+1;
        END IF;
    END LOOP;
    DBMS_OUTPUT.PUT_LINE(CNT);
END;
/



SELECT TO_NUMBER('100');
/



--PROCEDURE
CREATE OR REPLACE PROCEDURE IS_SENIOR (EID IN VARCHAR2) IS
    JDATE DATE;
    YEARS NUMBER;
BEGIN
    SELECT HIRE_DATE INTO JDATE 
    FROM EMPLOYEES
    WHERE EMPLOYEE_ID = EID;
    YEARS := ((MONTHS_BETWEEN(SYSDATE, JDATE))/12);
    IF YEARS >= 10 THEN
        DBMS_OUTPUT.PUT_LINE('SENIOR');
    ELSE 
        DBMS_OUTPUT.PUT_LINE('NOT');
    END IF;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        DBMS_OUTPUT.PUT_LINE('NOT FOUND');
    WHEN TOO_MANY_ROWS THEN
        DBMS_OUTPUT.PUT_LINE('MULTIPLE FOUND');
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('IDK WHAT HAPPENED');
END;
/
BEGIN
    IS_SENIOR(1005);
    IS_SENIOR(100);
END;
/



--FUNCTIONS
CREATE OR REPLACE FUNCTION IS_SENIOR_FUNC (EID IN VARCHAR2) 
RETURN VARCHAR2 IS
    JDATE DATE;
    YEARS NUMBER;
BEGIN
    SELECT HIRE_DATE INTO JDATE 
    FROM EMPLOYEES
    WHERE EMPLOYEE_ID = EID;
    YEARS := ((MONTHS_BETWEEN(SYSDATE, JDATE))/12);
    IF YEARS >= 10 THEN
        RETURN 'SENIOR';
    ELSE 
        RETURN 'NOT';
    END IF;
    RETURN ':(';
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RETURN 'NOT FOUND';
    WHEN TOO_MANY_ROWS THEN
        RETURN 'MULTIPLE FOUND';
    WHEN OTHERS THEN
        RETURN 'IDK WHAT HAPPENED';
END;
/
BEGIN
    DBMS_OUTPUT.PUT_LINE(IS_SENIOR_FUNC(105));
END;
/



-- TRIGGER
CREATE TABLE STUDENTS(
    STUDENT_NAME VARCHAR2(100),
    CGPA NUMBER
);
/

CREATE OR REPLACE TRIGGER HELLO_WORLD
AFTER INSERT
ON STUDENTS
BEGIN
    DBMS_OUTPUT.PUT_LINE('Hello_World!');
END;
/
INSERT INTO STUDENTS VALUES ('IRTIZA', 3.90);
/



-- 22 B 1:

-- COPY TABLE
CREATE TABLE employees_copy AS
SELECT * FROM employees;
COMMIT;
/

CREATE OR REPLACE FUNCTION Exchange_Employees (
    MID1 IN VARCHAR2, 
    MID2 IN VARCHAR2
) RETURN VARCHAR2 
IS
    EID1 NUMBER(6, 0);
    DEP1 NUMBER(4, 0);
    SAL1 NUMBER(8, 2);

    EID2 NUMBER(6, 0);
    DEP2 NUMBER(4, 0);
    SAL2 NUMBER(8, 2);
BEGIN
    
    SELECT EMPLOYEE_ID, DEPARTMENT_ID, SALARY
    INTO EID1, DEP1, SAL1
    FROM (
        SELECT EMPLOYEE_ID, DEPARTMENT_ID, SALARY
        FROM EMPLOYEES_COPY
        WHERE MANAGER_ID = MID1
        ORDER BY SALARY ASC
    ) 
    WHERE ROWNUM = 1;

    -- SIMILARLY, FOR EMPLOYEE2

    UPDATE EMPLOYEES_COPY
     SET DEPARTMENT_ID = DEP2,
         SALARY = SALARY + 0.5* ABS(SAL1-SAL2),
         MANAGER_ID = MID2
    WHERE EMPLOYEE_ID = EID1;

    -- SIMILARLY, SECOND

    COMMIT;

    RETURN 'Employees have been successfully exchanged.';

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        RETURN 'DATA MISSING';
    WHEN OTHERS THEN
        RETURN 'An error occurred during the exchange process.';
END;
/


-- 22 B 2 :
CREATE OR REPLACE PROCEDURE LOCATION_SALARY_REPORT 
IS 
    RNK NUMBER;
BEGIN 
    RNK := 1;
    FOR R IN (
        WITH EMP_TABLE AS (
            SELECT E.SALARY,
                   E.JOB_ID,
                   J.JOB_TITLE,
                   LOC.CITY
            FROM EMPLOYEES E
            JOIN JOBS J
                ON E.JOB_ID = J.JOB_ID
            JOIN DEPARTMENTS D
                ON E.DEPARTMENT_ID = D.DEPARTMENT_ID
            JOIN LOCATIONS LOC
                ON D.LOCATION_ID = LOC.LOCATION_ID
            JOIN COUNTRIES CO
                ON LOC.COUNTRY_ID = CO.COUNTRY_ID
            JOIN REGIONS RG
                ON CO.REGION_ID = RG.REGION_ID
        )
        SELECT CITY, COUNT(*) EMP_COUNT, ROUND(AVG(SALARY), 2) AVG_SALARY, 
            (
                SELECT JOB_TITLE 
                FROM EMP_TABLE E2
                WHERE E2.SALARY = (SELECT MAX(SALARY) FROM EMP_TABLE E3 WHERE E3.CITY = E1.CITY)
                AND ROWNUM = 1
            ) AS TOP_JOB
        FROM EMP_TABLE E1
        GROUP BY CITY
            ORDER BY COUNT(*) ASC, AVG(SALARY) DESC
    )
    LOOP
        DBMS_OUTPUT.PUT_LINE(
            'Rank: ' || RNK ||
            ' | City: ' || R.CITY ||
            ' | Employees: ' || R.EMP_COUNT ||
            ' | Avg Salary: ' || R.AVG_SALARY ||
            ' | Highest Paying Job: ' || R.TOP_JOB
        );
        RNK := RNK + 1;
    END LOOP;

END;
/
BEGIN
    LOCATION_SALARY_REPORT();
END;
/


-- 22 B 3:
CREATE OR REPLACE TRIGGER trg_transfer_employee
    AFTER UPDATE OF department_id ON employees
    FOR EACH ROW
    WHEN (OLD.department_id IS NOT NULL AND NEW.department_id != OLD.department_id)
DECLARE
    -- Variable Declarations
    v_curr_date             DATE;
    v_work_instead_id       employees.employee_id%TYPE;
    v_prev_manager_id       employees.manager_id%TYPE;
    v_prev_salary           employees.salary%TYPE;
    v_closest_salary        employees.salary%TYPE := NULL;
    v_diff                  NUMBER := NULL;
    v_new_salary            NUMBER;
    v_prev_manager_subcount NUMBER;
    v_new_manager_id        employees.manager_id%TYPE;
    v_min_diff              NUMBER := NULL;

BEGIN
    v_curr_date := SYSDATE;
    v_prev_salary := :OLD.salary;
    v_prev_manager_id := :OLD.manager_id;

    -- STEP 1: Record the transfer in the history table
    INSERT INTO Transfers (
        employee_id, 
        new_department, 
        transfer_date
    )
    VALUES (
        :OLD.employee_id, 
        :NEW.department_id, 
        v_curr_date
    );

    -- STEP 2: Logic for employees with an assigned manager
    IF v_prev_manager_id IS NOT NULL THEN
        
        -- Find the employee with the closest salary under the same manager

        /*
            THIS PART COULD BE DONE WITH : SELECT ... INTO ...
        */

        FOR emp IN (
            SELECT employee_id, salary
            FROM employees 
            WHERE manager_id = v_prev_manager_id
              AND employee_id != :OLD.employee_id
        )
        LOOP
            IF v_diff IS NULL OR ABS(emp.salary - v_prev_salary) < v_diff THEN
                v_diff            := ABS(emp.salary - v_prev_salary);
                v_work_instead_id := emp.employee_id;
                v_closest_salary  := emp.salary;
            END IF;
        END LOOP;


        -- If a "stand-in" employee was found, update their salary and the log
        IF v_work_instead_id IS NOT NULL THEN
            v_new_salary := v_closest_salary + (0.5 * v_prev_salary);
            
            UPDATE employees 
            SET salary = v_new_salary
            WHERE employee_id = v_work_instead_id;

            UPDATE Transfers
            SET employee_working_instead_of_him = v_work_instead_id
            WHERE employee_id = :OLD.employee_id
              AND transfer_date = v_curr_date;
        END IF;


        -- STEP 3: Assign a new manager in the new department
        -- Get the subordinate count of the previous manager
        SELECT COUNT(*) 
        INTO v_prev_manager_subcount 
        FROM employees
        WHERE manager_id = v_prev_manager_id;

        -- Find a manager in the new dept with a similar workload (subordinate count)
        FOR mgr IN ( 
            SELECT manager_id, COUNT(*) AS sub_count
            FROM employees 
            WHERE department_id = :NEW.department_id
              AND manager_id IS NOT NULL
            GROUP BY manager_id
        )
        LOOP
            IF v_min_diff IS NULL OR ABS(mgr.sub_count - v_prev_manager_subcount) < v_min_diff THEN
                v_min_diff       := ABS(mgr.sub_count - v_prev_manager_subcount);
                v_new_manager_id := mgr.manager_id;
            END IF;
        END LOOP;

        -- Update the transferred employee's manager record
        IF v_new_manager_id IS NOT NULL THEN
            UPDATE employees
            SET manager_id = v_new_manager_id
            WHERE employee_id = :NEW.employee_id;
        END IF;
        
    END IF;
END;
/