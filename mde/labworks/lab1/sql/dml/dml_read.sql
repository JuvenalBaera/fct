select * from cliente;
select * from instalacao;
select * from contrato;
select * from dispositivo;
select * from faturacao;


-- CLIENTES QUE NÃO TEM INSTALAÇÃO 
select * from cliente left join instalacao on cliente.id = instalacao.cliente_id where instalacao.cliente_id is null;

-- INSTALAÇÃO COM CLIENTE
select * from cliente join instalacao on cliente.id = instalacao.cliente_id;

-- contrato com # faturações
select contrato.id as contrato, count(*) as "# faturas" from contrato 
join faturacao on contrato.id = faturacao.contrato_id group by faturacao.contrato_id;

-- quantos dispositivos há numa instalação
select instalacao.id as instalacao, count(*) as "# dispositivo" from instalacao join dispositivo
on instalacao.id = dispositivo.instalacao_id
group by dispositivo.instalacao_id;

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
select i.id, d.data_instalacao, d.modelo from dispositivo as d join instalacao as i
on d.instalacao_id = i.id where i.id = 2 and d.data_instalacao between "2023-01-01" and "2023-12-31";

call dispositivo_instalacao_intervalo(2, "2023-01-01", "2023-12-31");
