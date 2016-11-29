
<!-- Incluimos encabezado -->
<?php include 'includes/header.inc'; ?>

<!-- Conformamos el formulario de login -->
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

<!-- Incluimos pie de página -->
<?php include 'includes/footer.inc'; ?>
