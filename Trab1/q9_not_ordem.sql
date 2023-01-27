select count(C_CUSTKEY)
from CUSTOMER left outer join ORDERS
on C_CUSTKEY = O_CUSTKEY
where O_ORDERKEY is NULL;