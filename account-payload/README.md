# Payload de Cuentas
Este es un programa de ejemplo para el modo RCM de la Nintendo Switch. Está basado en [TegraExplorer](https://github.com/suchmememanyskill/TegraExplorer/releases). Muestra datos sensibles almacenados en la consola tales como:
- Números de serie
- Conexiones WiFi con contraseñas sin cifrar
- Usuario, correo y contraseña de la cuenta de Nintendo (NNID)
- Usuario, correo y contraseña de la cuenta de Twitter (Si está vinculada)

Este programa ha sido utilizado como demostración en la conferencia "**Explotando Vulnerabilidades en Consolas de Videojuegos**" en la [AsturCON.tech](https://asturcon.tech/)
# Uso
Para ejecutarlo debes seguir los siguientes pasos:
1. Extraer los archivos `8000000000000010`, `0000000000000057`, `8000000000001060` con  [TegraExplorer](https://github.com/suchmememanyskill/TegraExplorer/releases) desde `EMMC/SYSTEM/save/...` o `EMUMMC/SYSTEM/save/` a la raíz de la tarjeta SD
2. Poner tu switch en [Modo RCM](https://switch.hacks.guide/user_guide/rcm/entering_rcm/) o usar una con modchip instalado.
3. Envía el payload almacenado en `output/AccountPayload.bin` con cualquier lanzador de payloads de Nintendo Switch como [JTegraNX](https://github.com/dylwedma11748/JTegraNX)
# Compilar
Para compilarlo, debes utilizar una máquina Linux (Preferiblemente Ubuntu) o WSL para Windows,
1. Instalar [dkp-pacman](https://devkitpro.org/wiki/devkitPro_pacman)
2. Añadir al path:
```bash
export DEVKITPRO=/opt/devkitpro
export DEVKITARM=${DEVKITPRO}/devkitARM
export DEVKITPPC=${DEVKITPRO}/devkitPPC
```
4. Instalar dependencias `sudo dkp-pacman -Sy devkitARM`
5. Clonar el repositorio `git clone https://github.com/josefl03/vulnerabilidades-consolas`
6. Entrar al directorio `cd vulnerabilidades-consolas/accounts-payload`
7. Ejecutar `make`
8. El programa estará ubicado dentro de `output/ImagePayload.bin`. Ejecutar con las instrucciones de [Uso](#Uso)