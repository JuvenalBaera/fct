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

-- CONTRATO
update contrato set preco = 50.00 where id = 1;
update contrato set preco = 20.97 where id = 2;
update contrato set preco = 70.44 where id = 3;
update contrato set preco = 90.78 where id = 4;
update contrato set preco = 10.90 where id = 5;
update contrato set preco = 40.72 where id = 6;
update contrato set preco = 50.56 where id = 7;
update contrato set preco = 66.55 where id = 8;
update contrato set preco = 93.45 where id = 9;
update contrato set preco = 33.21 where id = 10;

-- ALTER
alter table instalacao add column tipo varchar(64) not null after id;
alter table contrato modify preco decimal(5,2) not null;


