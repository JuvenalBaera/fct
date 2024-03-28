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