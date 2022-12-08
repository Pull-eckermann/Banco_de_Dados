select count(*)
from(
    select distinct O_CUSTKEY
    from ORDERS
    except
    select distinct O_CUSTKEY               
    from ORDERS
    where O_COMMENT like '%special request%'
);