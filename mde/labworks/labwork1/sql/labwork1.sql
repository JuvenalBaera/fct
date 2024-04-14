-- MySQL Workbench Forward Engineering

SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
-- -----------------------------------------------------
-- Schema labwork1
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `labwork1` ;

-- -----------------------------------------------------
-- Schema labwork1
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `labwork1` ;
USE `labwork1` ;

-- -----------------------------------------------------
-- Table `cliente`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `cliente` ;

CREATE TABLE IF NOT EXISTS `cliente` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nome` VARCHAR(127) NOT NULL,
  `endereco` VARCHAR(255) NOT NULL,
  `nif` VARCHAR(10) NOT NULL,
  `telefone` VARCHAR(15) NOT NULL,
  PRIMARY KEY (`id`),
  UNIQUE INDEX `nif_UNIQUE` (`nif` ASC))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `contrato`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `contrato` ;

CREATE TABLE IF NOT EXISTS `contrato` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `data_inicio` DATE NOT NULL,
  `data_fim` DATE NOT NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `instalacao`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `instalacao` ;

CREATE TABLE IF NOT EXISTS `instalacao` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `tipo` VARCHAR(64) NOT NULL,
  `endereco` VARCHAR(255) NOT NULL,
  `cliente_id` INT NULL,
  `contrato_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_instalacao_cliente_idx` (`cliente_id` ASC),
  INDEX `fk_instalacao_contrato1_idx` (`contrato_id` ASC),
  CONSTRAINT `fk_instalacao_cliente`
    FOREIGN KEY (`cliente_id`)
    REFERENCES `cliente` (`id`)
    ON DELETE CASCADE
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_instalacao_contrato1`
    FOREIGN KEY (`contrato_id`)
    REFERENCES `contrato` (`id`)
    ON DELETE CASCADE
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `dispositivo`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `dispositivo` ;

CREATE TABLE IF NOT EXISTS `dispositivo` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `modelo` VARCHAR(64) NOT NULL,
  `tipo` VARCHAR(64) NOT NULL,
  `data_instalacao` DATE NOT NULL,
  `estado` TINYINT NOT NULL,
  `especificacao` VARCHAR(255) NULL,
  `instalacao_id` INT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_dispositivo_instalacao1_idx` (`instalacao_id` ASC),
  CONSTRAINT `fk_dispositivo_instalacao1`
    FOREIGN KEY (`instalacao_id`)
    REFERENCES `instalacao` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `faturacao`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `faturacao` ;

CREATE TABLE IF NOT EXISTS `faturacao` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `data` DATE NOT NULL,
  `estado` TINYINT NOT NULL,
  `contrato_id` INT NOT NULL,
  `preco` DECIMAL(5,2) NOT NULL,
  PRIMARY KEY (`id`),
  INDEX `fk_faturacao_contrato1_idx` (`contrato_id` ASC),
  CONSTRAINT `fk_faturacao_contrato1`
    FOREIGN KEY (`contrato_id`)
    REFERENCES `contrato` (`id`)
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `servico`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `servico` ;

CREATE TABLE IF NOT EXISTS `servico` (
  `id` INT NOT NULL AUTO_INCREMENT,
  `nivel` VARCHAR(45) NULL,
  PRIMARY KEY (`id`))
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `contrato_servico`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `contrato_servico` ;

CREATE TABLE IF NOT EXISTS `contrato_servico` (
  `contrato_id` INT NOT NULL,
  `servico_id` INT NOT NULL,
  PRIMARY KEY (`contrato_id`, `servico_id`),
  INDEX `fk_contrato_has_servico_servico1_idx` (`servico_id` ASC),
  INDEX `fk_contrato_has_servico_contrato1_idx` (`contrato_id` ASC),
  CONSTRAINT `fk_contrato_has_servico_contrato1`
    FOREIGN KEY (`contrato_id`)
    REFERENCES `contrato` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE,
  CONSTRAINT `fk_contrato_has_servico_servico1`
    FOREIGN KEY (`servico_id`)
    REFERENCES `servico` (`id`)
    ON DELETE CASCADE
    ON UPDATE CASCADE)
ENGINE = InnoDB;


SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;
