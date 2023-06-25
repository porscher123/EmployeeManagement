create table logs(
    id int(11) PRIMARY KEY AUTOINCREMENT
    operation varchar(20) not null comment '操作类型, insert/update/delete',
    operate_time datetime not null comment '操作时间',
    operate_id int(11) not null comment '操作ID',
    operate_params varchar(500) comment '操作参数',
);

-- 插入数据
create trigger insert_trigger
    before insert on employee for each row
begin
    insert into logs(operation,operate_time,operate_id,operate_params)
        VALUES ('insert', now(), new.employee_id, concat('插入的内容：id=',new.employee_id,',name=',new.name,',sex=',new.sex,',age=',new.age,',phone=',new.phone_number,',education=',new.education_backgroud,',title=',new.job_title,',department=',new.department_id,',salary=',new.salary));

end;

-- 修改数据
create trigger update_trigger
    before update on employee for each row
begin
    insert into logs(operation,operate_time,operate_id,operate_params)
        VALUES ('update', now(), new.employee_id, concat('插入的内容：id=',old.employee_id,',name=',OLD.name,',sex=',OLD.sex,',age=',old.age,',phone=',old.phone_number,',education=',old.education_backgroud,',title=',old.job_title,',department=',old.department_id,',salary=',old.salary,
            ' |更新之后的内容：id=',new.employee_id,',name=',new.name,',sex=',new.sex,',age=',new.age,',phone=',new.phone_number,',education=',new.education_backgroud,',title=',new.job_title,',department=',new.department_id,',salary=',new.salary));


end;
-- 删除数据
create trigger delete_trigger
    before delete on employee for each row
begin
    insert into logs(operation,operate_time,operate_id,operate_params)
        VALUES (null, 'delete', now(), old.employee_id, concat('删除之前的内容：id=',old.employee_id,',name=',OLD.name,',sex=',OLD.sex,',age=',old.age,',phone=',old.phone_number,',education=',old.education_backgroud,',title=',old.job_title,',department=',old.department_id,',salary=',old.salary));

end;

show triggers;


-- 建立索引
create  index  idx_emp_name on employee(name);

create index idx_emp_sal on employee(salary);

show index from employee;