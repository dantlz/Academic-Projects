DROP DATABASE if exists tianlinz;

CREATE DATABASE tianlinz;

USE tianlinz;

CREATE TABLE Users (
  username varchar(50) primary key not null,
  password varchar(50) not null
);

CREATE TABLE Files (
  username varchar(50) not null,
  filename varchar(50) not null,
  fileContent longtext not null 
);