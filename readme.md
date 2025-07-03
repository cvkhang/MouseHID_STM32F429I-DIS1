Dự án TouchGFX mẫu cho bo mạch **STM32F429I-DISCO**. Mặc định dự án sử dụng
`STM32CubeIDE` làm môi trường phát triển.

## Công cụ và phiên bản
- **STM32CubeMX 6.14.0**
- **TouchGFX 4.25.0**
- **Firmware Package F4 1.28.1**
- **STM32CubeIDE** (khuyến nghị bản 1.13 trở lên)
- **EWARM 8.50.9** hoặc **MDK-ARM** (tuỳ chọn)
- **STM32CubeProgrammer** để nạp firmware

## Hướng dẫn cài đặt

1. Cài đặt các công cụ với phiên bản như trên.
2. Tải mã nguồn về bằng Git.
3. Mở file `STM32F429I_DISCO_REV_D01.ioc` bằng STM32CubeMX và chọn IDE mong muốn.
4. Mở dự án tương ứng trong thư mục `STM32CubeIDE` (hoặc EWARM/MDK-ARM) và biên dịch.
5. Sử dụng STM32CubeProgrammer để nạp chương trình vào bo mạch.
