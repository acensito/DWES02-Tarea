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
</head>

<body>
    
    <h1 class="centrado">TAREA 3: BANCO DWES</h1>
    <h2 class="centrado">Felipe Rodríguez Gutiérrez</h2>
    
    <!-- Mostramos el formulario inicial -->
    <div class="container">
        <form id='signup' action='login.php' method='post'>
        <div class='header'>
        <h3>Elija una acción</h3>
        </div>
            <div class='inputs'>
                <input id='submit' type='submit' name='accion' value='ADMINISTRAR USUARIOS' />
                <input id='submit' type='submit' name='accion' value='INICIAR SESION' />
            </div>
        </form>
    </div>

    <div id="pie">Felipe Rodriguez Gutiérrez - DWES Tarea 3 - Curso 2015/2016</div>
</html>