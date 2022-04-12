
Data Base Gestor
================

Proyecto final BD2.

### Queries


###### Create Table

    CREATE TABLA Alumnos CHAR(30) nombres CHAR(30) apellidos INTEGER edad ;


    CREATE TABLA Tb_estudiante_30000 INTEGER ID_est CHAR(30) nom CHAR(30) ape INTEGER edad ;

###### Insert

    INSERTAR EN Alumnos VALORES Tilin1 Kowalsky 18 ;

###### Select

    SELECT * FROM Tb_estudiante_30000 WHERE ID_est = 28999 ;

###### Delete

    BORRAR DESDE [Table] DONDE [comlumn][sentence][value]


    DELETE FROM Alumnos WHERE nombres = Tilin ;

###### Update


### Working with Index

    CREATE INDEX indi2 ON Alumnos (edad);


    CREATE INDEX IDX_30000 ON Tb_estudiante_30000 (ID_est);

###### Select

    SELECT * FROM Alumnos WHERE edad = 18 IDX = indi2.idx ;


    SELECT * FROM Tb_estudiante_30000 WHERE id = 28999 IDX = IDX_30000.idx ;

###### Insert

    INSERTAR CON INDICE EN Tb_estudiante_30000 VALORES 30001 jorge luis 24 INDICE IDX_30000.idx(ID_est) S(30001) ;

###### Delete

    ELIMINAR CON INDICE EN Tb_estudiante_30000 WHERE ID_est = 30001 INDICE IDX_30000.idx ;


