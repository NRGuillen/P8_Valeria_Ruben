#!/bin/bash

# Verificar si existe un repositorio remoto
if git remote -v | grep -q origin; then
    echo "Repositorio remoto 'origin' ya está configurado."
else
    # Si no existe un repositorio remoto, agregar uno
    echo "No se encuentra el repositorio remoto. Configurando 'origin'..."
    echo "Introduce la URL de tu repositorio GitHub:"
    read repo_url
    git remote add origin $repo_url
    echo "Repositorio remoto 'origin' configurado."
fi

# Verificar en qué rama estamos
current_branch=$(git branch --show-current)
echo "Estás en la rama '$current_branch'."

# Asegurarnos de estar en la rama 'main'
if [ "$current_branch" != "main" ]; then
    echo "Cambiando a la rama 'main'..."
    git checkout main
fi

# Agregar todos los archivos
echo "Agregando archivos al área de preparación..."
git add .

# Hacer commit de los cambios
echo "Introduce el mensaje del commit:"
read commit_message
git commit -m "$commit_message"

# Subir los cambios a GitHub
echo "Subiendo los cambios al repositorio remoto 'origin'..."
git push -u origin main

echo "¡Todo listo! Los archivos han sido subidos a 'main' en GitHub."

