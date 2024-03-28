-- UPDATE
update contrato set duracao = 5 where duracao = 0;

update instalacao set tipo = "loja" where id = 1;
update instalacao set tipo = "casa" where id = 2;
update instalacao set tipo = "escritório" where id = 3;
update instalacao set tipo = "apartamento" where id = 4;
update instalacao set tipo = "loja" where id = 5;
update instalacao set tipo = "apartamento" where id = 6;
update instalacao set tipo = "loja" where id = 7;
update instalacao set tipo = "casa" where id = 8;
update instalacao set tipo = "escritório" where id = 9;
update instalacao set tipo = "loja" where id = 10;

-- ALTER
alter table instalacao add column tipo varchar(64) not null after id;

