<?php include 'includes/header.inc';?>
    
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

<?php include 'includes/footer.inc';?>
