SELECT m1.title FROM movies m1
JOIN stars s1 ON s1.movie_id == m1.id
JOIN people p1 ON s1.person_id == p1.id AND p1.name == "Chadwick Boseman"
JOIN ratings r1 ON r1.movie_id == s1.movie_id
ORDER BY r1.rating DESC
LIMIT 5;

