-- RF4
delimiter $$
create procedure cliente_tipo_instalacao(in tipo varchar(64))
begin
	select c.nome, c.endereco, c.nif, c.telefone, i.tipo  
		   from cliente as c 
           join instalacao as i on c.id = i.cliente_id where i.tipo = tipo;
end $$
delimiter ;


-- RF5
delimiter $$
create procedure cliente_tipo_servico(in nivel varchar(64))
begin
	select c.id, c.nome, s.nivel from cliente as c join instalacao as i 
	on c.id = i.cliente_id join contrato as ct
	on i.contrato_id = ct.id join contrato_servico as cs
	on ct.id = cs.contrato_id join servico as s
	on cs.servico_id = s.id
	where s.nivel = nivel;
end $$
delimiter ;


-- RF6
delimiter $$
create procedure dispositivo_instalacao_intervalo(in id_instalacao int, d_inicio date, d_fim date)
begin
	select i.id, d.data_instalacao, d.modelo from dispositivo as d join instalacao as i
	on d.instalacao_id = i.id where i.id = id_instalacao and d.data_instalacao between d_inicio and d_fim;
end $$
delimiter ;


-- RF7 
delimiter $$
create procedure media_faturacao_idintervalo(in c_id int, d_inicio date, d_fim date, estado tinyint)
begin
	select avg(f.preco) as media from cliente as c join instalacao as i 
	on c.id = i.cliente_id join contrato as ct
	on i.contrato_id = ct.id  join faturacao as f
	on f.contrato_id = ct.id 
	where c.id = c_id and f.estado = estado
	and ct.data_inicio between d_inicio and d_fim;
end $$
delimiter ;

-- Com função
delimiter $$
create function media_faturacao_id_intervalo_fun(c_id int, d_inicio date, d_fim date, estado tinyint)
returns decimal(5, 2)
begin
	declare med decimal(5, 2);
    
    select avg(f.preco) as media into med 
    from cliente as c join instalacao as i 
	on c.id = i.cliente_id join contrato as ct
	on i.contrato_id = ct.id  join faturacao as f
	on f.contrato_id = ct.id 
	where c.id = c_id and f.estado = estado
	and ct.data_inicio between d_inicio and d_fim;

    return med;
end; $$
delimiter ;


-- RF10
-- top 10 clientes com mais instalações (view)
create view top_clientes as
	select cliente.id, nome, count(*) as nr_instalacao 
	from cliente join instalacao
	on cliente.id = instalacao.cliente_id
	group by cliente.id
	order by nr_instalacao desc;


-- RF11
delimiter $$
create procedure numero_cliente_tipo_servico(nivel varchar(64))
begin
	select count(*) as "# clientes", s.nivel from cliente as c join instalacao as i 
	on c.id = i.cliente_id join contrato as ct
	on i.contrato_id = ct.id join contrato_servico as cs
	on ct.id = cs.contrato_id join servico as s
	on cs.servico_id = s.id
	where s.nivel = nivel;
end $$
delimiter ;

-- valor em falta por pagar dum cliente
select c.nome, c.nif, f.data, sum(f.preco) as total from cliente as c 
join instalacao as i
on c.id = i.cliente_id 
join contrato as cnt
on cnt.id = i.contrato_id 
join faturacao as f
on f.contrato_id = cnt.id
where c.id = 77 and f.estado = 0; -- 22, 61, 37, 66
