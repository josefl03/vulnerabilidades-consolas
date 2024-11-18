 Explotando Vulnerabilidades en Consolas de Videojuegos
 Este repositorio contiene la presentación y la información mencionada en la conferencia "***Explotando Vulnerabilidades en Consolas de Videojuegos***", que se llevó a cabo en la [AsturCON.tech](https://asturcon.tech/) el **8 de Noviembre de 2024** en **Avilés**.
 ![[banner.png]]
# Materiales
**Presentación**: [Google Slides](https://docs.google.com/presentation/d/1NGB3Oazw3SAv7Olow2h5vGKE30gEoAXohU6n8PbAEGQ/edit?usp=sharing), también disponible en [PDF](presentacion.pdf),

**Fuentes** y demás **información**: Sección [Información y Enlaces](#Información y Enlaces)

**Programas** de la Nintendo Switch:
- [image-payload](image-payload/): Para mostrar el logo de la conferencia
- [account-payload](account-payload/): Para mostrar la información de cuentas de usuario y contraseñas, redes conectadas y contraseñas, números de serie, etc.
Basados en [TegraExplorer](https://github.com/suchmememanyskill/TegraExplorer). Información de cómo compilarlos en cada carpeta

**Vídeos PoC** de los programas:
- [poc-image.mp4](poc-image.mp4): Vídeo mostrando el programa para enseñar el logo de la conferencia
- [poc-account.mp4](poc-account.mp4): Vídeo con el funcionamiento del programa que muestra la información de usuario y contraseñas
# Información y Enlaces
Mi perfil de **Linkedin**: [Jose Fernández López](https://www.linkedin.com/in/jose-f-l/)

Xbox Kinect
[NSA espía usuarios a través de Xbox Kinect](https://www.cinemablend.com/games/Xbox-Kinect-NSA-Spying-Was-Done-Consent-Claims-Microsoft-60970.html)
[Cómo los usuarios hackearon el Xbox Kinect, paso por paso](https://learn.adafruit.com/hacking-the-kinect/overview)

Wii Motion y PlayStation Move (Aplicable a muchos más mandos)
[Análisis de vulnerabilidades en Bluetooth 2.0](https://openaccess.uoc.edu/bitstream/10609/106368/6/eduseseTFM0120memoria.pdf)

Brechas de datos en empresas de videojuegos
[Recopilación y explicación de 11 de ellas](https://www.eset.com/uk/about/newsroom/blog/11-massive-video-game-companies-recently-targeted-by-cybercriminals/?srsltid=AfmBOoreHKzGEjVnqBSdCtAsa8BfgjmB98pGPik1t8PAb6LS80OMlDU6)
[Algunas más, algo más detallado](https://plextrac.com/blog/the-history-of-cybersecurity-in-video-games/)

Herramientas de Ingeniería Inversa
[Ghidra (NSA)](https://ghidra-sre.org/) - Gratis y open-source (Recomendada)
[IDA (hex-rays)](https://hex-rays.com/) - Versión gratuita disponible

Extraer Firmwares
[Pequeña introducción a extraer Firmwares (Con bastantes casos)](https://slava-moskvin.medium.com/extracting-firmware-every-method-explained-e94aa094d0dd)

El Procesador
[Contador de Programa, resumido](https://www.geeksforgeeks.org/what-is-program-counter/)
[La Pila y el Contador de Programa, más detallado](https://www.renesas.com/en/support/engineer-school/mcu-programming-peripherals-06?srsltid=AfmBOooXLzNvPHFPW7Zkdcq9VGPTbl6mkELFYvXMrq_KIvrh7kkAgPlg)
[Espacio de Kernel, espacio de Usuario, bien explicado](https://www.form3.tech/blog/engineering/linux-fundamentals-user-kernel-space)

3DS
[Hardware](https://3dbrew.org/wiki/Hardware)
[Encriptado en la 3DS](https://yifan.lu/2016/04/06/the-3ds-cryptosystem/)

[Vulnerabilidad del WebKit explicada (use-after-free)](https://yifan.lu/2015/01/10/reversing-gateway-ultra-first-stage-part-1/)
[Explicación buffer-overflows](https://www.coengoedegebure.com/buffer-overflow-attacks-explained/)
[Exploits de juegos (buffer-overflow, ejemplo con Zelda Ocarina of Time)](https://github.com/yellows8/oot3dhax)
[Buffer-overflow remoto (ENLBufferPwn)](https://github.com/PabloMK7/ENLBufferPwn)
[Buffer-overflow remoto (SwapNote RCE)](https://hackerone.com/reports/923240)

Wii
[Hardware](https://wiibrew.org/wiki/Hardware)
[Cadena de confianza en la Wii (resumido)](http://wiibrew.org/wiki/Boot_process)
[Cadena de confianza en la Wii (detallado)](https://www.copetti.org/writings/consoles/wii/)
[Módulo OTP (One-Time-Programmable)](https://wiibrew.org/wiki/Hardware/OTP)

[Vulnerabilidad en la cadena de confianza](https://wiibrew.org/wiki/Wii_system_flaws#boot1)
[Vuinerabilidad en tablero de mensajes (BannerBomb)](https://please.hackmii.com/)
[Vulnerabilidad en Bluetooth (Bluebomb)](https://github.com/Fullmetal5/bluebomb)

PS4
[Hardware](https://cturt.github.io/ps4.html)
[ASLR (Address Space Layout Randomization) + Ejemplos en Linux](https://book.hacktricks.xyz/binary-exploitation/common-binary-protections-and-bypasses/aslr)
[Hypervisor PS4](https://www.psdevwiki.com/ps5/Hypervisor)
[eFuses (Fusibles para prevenir actualizaciones)](https://gbatemp.net/threads/faq-efuses.494404/)
[FreeBSD en PS4](https://www.psdevwiki.com/ps4/Syscalls)

[Buffer-overflow remoto (PPPwn)](https://github.com/TheOfficialFloW/PPPwn)

Xbox Series
[Dev Mode](https://www.reddit.com/r/XboxRetailHomebrew/comments/12ikitn/guide_how_to_activate_dev_mode_and_install_dev/)
[Microsoft banea emuladores, provocando el caos](https://atomix.vg/microsoft-comenzo-a-bloquear-emuladores-en-xbox-series-xs/)

[Exploit en GameScript (Collateral Damage)](https://github.com/exploits-forsale/collateral-damage)

PS5
[Hardware](https://hardwear.io/usa-2023/presentation/next-gen-exploitation-exploring-the-PS5-security-landscape.pdf)
[ASan (Address Sanitization)](https://source.android.com/docs/security/test/asan)
[XOM (eXecute Only Memory)](https://ps5dev.github.io/ps5-wiki/xom)

[Exploit Java VM (bd-jb)](https://github.com/TheOfficialFloW/bd-jb) y su [Charla explicándolo](https://www.youtube.com/watch?v=jyyCOoWksbg)
[Exploit del Hypervisor (Bypervisor)](https://github.com/PS5Dev/Byepervisor/tree/main)
[Exploit buffer-overflow remoto IPv6 FreeBSD (CVE-2020-7457)](https://nvd.nist.gov/vuln/detail/CVE-2020-7457)
[PPPwn (También en PS5)](https://github.com/TheOfficialFloW/PPPwn)

Switch
[Hardware](https://switchbrew.org/wiki/Hardware)
[Manual Tegra X1 para desarrolladores](https://developer.nvidia.com/embedded/downloads#?search=X1)

[Exploit Hotspot explicado](https://www.bitdefender.com/en-us/blog/hotforsecurity/using-iphone-bug-hack-switch)
[Exploit WebKit (PEGASUS, CVE-2016-4657)](https://nvd.nist.gov/vuln/detail/cve-2016-4657)
[Exploit de los servicios (smhax)](https://switchbrew.org/wiki/Switch_System_Flaws#BootImagePackage_System_Modules)
[Exploits del Kernel](https://switchbrew.org/wiki/Switch_System_Flaws#Kernel)
[Exploit de la Máquina Virtual (jamais vu)](https://switchbrew.org/wiki/Switch_System_Flaws#TrustZone)
[Exploit del módulo WiFi, explicado](https://www.blackhat.com/docs/us-17/thursday/us-17-Artenstein-Broadpwn-Remotely-Compromising-Android-And-iOS-Via-A-Bug-In-Broadcoms-Wifi-Chipsets.pdf)
[Modo RCM](https://switch.hacks.guide/user_guide/rcm/entering_rcm/) y exploit [Fusèe Gelee](https://misc.ktemkin.com/fusee_gelee_nvidia.pdf)