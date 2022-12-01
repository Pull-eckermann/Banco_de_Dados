select count(distinct O_CUSTKEY)
from ORDERS
where O_COMMENT like "%special request%" 
and O_COMMENT not like "%unusual package%";