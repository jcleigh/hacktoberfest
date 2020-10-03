-- MSSQL non-recursive

SELECT CASE
	WHEN number % 3 = 0 AND number % 5 = 0 THEN 'FizzBuzz'
	WHEN number % 5 = 0 THEN 'Buzz'
	WHEN number % 3 = 0 THEN 'Fizz'
	ELSE CAST(number as VARCHAR(3)) END AS 'FizzBuzz Results'
FROM (
	SELECT DISTINCT number
	FROM master.dbo.[spt_values]
	WHERE number BETWEEN 1 AND 100
	) numbers