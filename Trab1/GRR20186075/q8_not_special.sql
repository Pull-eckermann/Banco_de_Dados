select count(distinct O_CUSTKEY)
from ORDERS
where O_COMMENT not like "%special request%";