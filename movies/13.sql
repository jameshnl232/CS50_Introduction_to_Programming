SELECT DISTINCT p.name FROM people p
JOIN stars s1 ON s1.person_id == p.id
JOIN movies m1 ON s1.movie_id == m1.id
JOIN stars s2 ON m1.id == s2.movie_id
JOIN people kb ON kb.id == s2.person_id AND kb.name == "Kevin Bacon" AND kb.birth == 1958
WHERE p.name != "Kevin Bacon";
