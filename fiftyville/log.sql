-- Keep a log of any SQL queries you execute as you solve the mystery.
-- See the report of the theft
SELECT description FROM crime_scene_reports WHERE day == 28 AND month == 7
AND YEAR == 2021 AND street == "Humphrey Street";
--See the security logs of the bakery on the crime day
SELECT activity FROM bakery_security_logs WHERE
day == 28 AND month == 7 AND year == 2021 AND hour == 10 AND minute == 16;
--See license_plate at the crime
SELECT DISTINCT p1.name, bsl1.activity, bsl1.hour, bsl1.minute FROM bakery_security_logs bsl1
JOIN people p1
JOIN bank_accounts ba1 ON ba1.person_id == p1.id
JOIN atm_transactions at1 ON at1.account_number == ba1.account_number 
WHERE bsl1.day == 28 AND bsl1.month == 7 AND bsl1.year == 2021
AND bsl1.hour == 10 AND 15 <= bsl1.minute <= 25
AND at1.transaction_type == "withdraw" 
AND at1.atm_location == "Leggett Street"
AND at1.day == 28 AND at1.month == 7 AND at1.year == 2021;

--see interview transcript 
SELECT name, transcript FROM interviews WHERE 
day == 28 AND month == 7 AND year == 2021 AND transcript LIKE "%bakery%";

--See some suspects who withdrew money on 28th July 2021 on Leggett Street
SELECT DISTINCT p1.name FROM people p1
JOIN bank_accounts ba1 ON ba1.person_id == p1.id
JOIN atm_transactions at1 ON at1.account_number == ba1.account_number 
WHERE at1.transaction_type == "withdraw" AND at1.atm_location == "Leggett Street"
AND at1.day == 28 AND at1.month == 7 AND at1.year == 2021;

--See some suspects who parked and made the phone call 
SELECT DISTINCT p1.name, p2.name FROM people p1
JOIN bakery_security_logs bsl1 ON bsl1.license_plate == p1.license_plate 
JOIN phone_calls pc1 ON pc1.caller == p1.phone_number
JOIN people p2 ON pc1.receiver == p2.phone_number
JOIN bank_accounts ba1 ON ba1.person_id == p1.id
JOIN atm_transactions at1 ON at1.account_number == ba1.account_number 
WHERE bsl1.day == 28 AND bsl1.month == 7 AND bsl1.year == 2021 
AND bsl1.hour == 10 AND 15 <= bsl1.minute <= 25
AND pc1.day == 28 AND pc1.month == 7 AND pc1.year == 2021 
AND pc1.duration <= 60
AND at1.transaction_type == "withdraw" 
AND at1.atm_location == "Leggett Street";

--Find the earliest flight on the 29.07.2021 and the destination
SELECT a1.city, a2.city, f1.hour, f1.minute FROM flights f1
JOIN airports a1 ON a1.id == f1.origin_airport_id 
JOIN airports a2 ON a2.id == f1.destination_airport_id
WHERE f1.day == 29 AND f1.month == 7 AND f1.year == 2021
ORDER BY f1.hour;

--find the thief
SELECT DISTINCT pe1.name AS caller, pe2.name AS receiver FROM people pe1 
JOIN bakery_security_logs bsl1 ON bsl1.license_plate == pe1.license_plate 
JOIN bank_accounts ba1 ON ba1.person_id == pe1.id
JOIN atm_transactions at1 ON at1.account_number == ba1.account_number
JOIN phone_calls pc1 ON pc1.caller == pe1.phone_number 
JOIN people pe2 ON pc1.receiver == pe2.phone_number
JOIN passengers pa1 ON pa1.passport_number == pe1.passport_number 
JOIN flights f1 ON pa1.flight_id == f1.id 
JOIN airports a1 ON f1.origin_airport_id == a1.id 
JOIN airports a2 ON f1.destination_airport_id == a2.id

WHERE f1.day == 29 AND f1.month == 7 AND f1.year == 2021
AND f1.hour == 8 AND f1.minute == 20
AND a1.city == "Fiftyville" AND a2.city == "New York City"

AND bsl1.day == 28 AND bsl1.month == 7 AND bsl1.year == 2021 
AND bsl1.hour == 10 AND bsl1.minute >= 15
AND bsl1.minute <= 25 AND bsl1.activity == "exit"

AND at1.transaction_type == "withdraw" 
AND at1.day == 28 AND at1.month == 7 AND at1.year == 2021
AND at1.atm_location == "Leggett Street"

AND pc1.day == 28 AND pc1.month == 7 AND pc1.year == 2021 
AND pc1.duration <= 60;
