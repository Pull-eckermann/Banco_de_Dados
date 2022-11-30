select a.C_NATIONKEY, b.O_CUSTKEY
from CUSTOMER A inner join ORDERS B
where a.C_CUSTKEY = b.O_CUSTKEY;