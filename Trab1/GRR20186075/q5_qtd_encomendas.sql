select N_NAME, count(O_ORDERKEY)
from(
  select *
  from NATION A, CUSTOMER B on a.N_NATIONKEY = b.C_NATIONKEY, ORDERS C
  where c.O_CUSTKEY = b.C_CUSTKEY
  )
group by N_NAME
order by count(O_ORDERKEY) desc
;