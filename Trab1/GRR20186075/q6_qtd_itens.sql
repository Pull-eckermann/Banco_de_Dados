select N_NAME, sum(a.L_QUANTITY)
from(
  select *
  from NATION A, CUSTOMER B on a.N_NATIONKEY = b.C_NATIONKEY, ORDERS C
  where c.O_CUSTKEY = b.C_CUSTKEY
  ), LINEITEM A
where O_ORDERKEY = a.L_ORDERKEY
group by N_NAME
order by sum(L_QUANTITY) desc
LIMIT 10
;