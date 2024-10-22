document.addEventListener("DOMContentLoaded", function () {
    const elementosTexto = document.querySelectorAll(".titulo, p, .carousel-caption, .footer");
  
    elementosTexto.forEach((elemento, index) => {
      // Añadir un retraso escalonado en la aparición de cada bloque de texto
      elemento.style.animationDelay = `${index * 1.5}s`;
      elemento.classList.add('aparecer');  // Clase que activa la animación
    });
  });