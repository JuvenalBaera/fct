select * from cliente;
select * from instalacao;
select * from contrato;
select * from contrato_servico;
select * from dispositivo;
select * from faturacao;
select * from servico;

select * from instalacao where contrato_id = 3;


-- RF4:
call cliente_tipo_instalacao("loja");
call cliente_tipo_instalacao("casa");
call cliente_tipo_instalacao("escritório");
call cliente_tipo_instalacao("apartamento");


-- RF5
call cliente_tipo_servico("Lowcost");
call cliente_tipo_servico("Normal");
call cliente_tipo_servico("Profissional");


-- RF6
call dispositivo_instalacao_intervalo(22, "2022-01-01", "2028-12-31");

-- RF7 
call  media_faturacao_idintervalo(22, "2022-06-02", "2026-05-02", 1);
select media_faturacao_id_intervalo_fun(22, "2022-06-02", "2026-05-02", 1) as media;
-- RF8

-- RF9
-- viualizar as datas de instalação de um dispositivo numa instalação
select d.instalacao_id, d.id, d.tipo, d.data_instalacao from instalacao as i join dispositivo as d
on i.id = d.instalacao_id
where d.instalacao_id = 15;

-- RF10
-- top 10 clientes com mais instalações
select * from top_clientes limit 5;

-- RF11
call numero_cliente_tipo_servico("Lowcost");
call numero_cliente_tipo_servico("Normal");
call numero_cliente_tipo_servico("Profissional");

-- RF12
call faturas_por_pagar_cliente(100);
-- RF13: Java
-- RF14
