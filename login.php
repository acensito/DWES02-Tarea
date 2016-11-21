<!DOCTYPE html>
<!-- Desarrollo Web en Entorno Servidor -->
<!-- Tema 3: Trabajar con bases de datos en PHP -->
<!-- Felipe Rodríguez Gutiérrez -->
<!-- Tarea: 03 Banco DWES -->
<html>
    
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <title>DWES - Tarea 3 - Felipe Rodríguez Gutiérrez</title>
    <link type="text/css" href="estilos.css" rel="stylesheet" />
    <?php include './includes/funciones.inc'; ?>
</head>

<body>
    
    <!-- Conformamos el formulario de login -->
    
    <h1 class="centrado">TAREA 3: BANCO DWES</h1>
    <h2 class="centrado">Felipe Rodríguez Gutiérrez</h2>
    
    <div class="container">
        <?php
        /*
         * El login pese a ser esteticamente el mismmo dependerá del boton 
         * pulsado, ya que dará acceso admin o al acceso de usuarios invocando
         * a la función acceso.
         */
            if (isset($_POST['accion'])) {
                $accion = $_POST['accion'];
                switch ($accion) {
                    case 'ADMINISTRAR USUARIOS':
                        acceso('admin');
                        break;
                    
                    case 'INICIAR SESION':
                        acceso('user');
                        break;
                }
            }
        ?>
    </div>

    <div id="pie">Felipe Rodriguez Gutiérrez - DWES Tarea 3 - Curso 2015/2016</div>
</html>