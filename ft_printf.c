#include <stdarg.h>
#include <unistd.h>


int	ft_print_str(char *str)
{
	int	i;
	
	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (ft_strlen(str) - 1);
}

int	ft_print_char(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_print_rev_str(char *hex)
{
	int	len;
	
	len = ft_strlen(hex);
	while (len--)
	{
		write(1, &hex[len], 1);
	}
	return (ft_strlen(hex));
}

int	ft_print_hex_up(unsigned int num)
{
	int	rem;
	int	i;
	char	*hex;
	
	i = 0;
	hex = malloc(sizeof(char) * 100);
	while (num > 0)
	{
		rem = num % 16;
		if (rem < 10)
			hex[i] = rem + 48;
		else
			hex[i] = rem + 55;
		num = num / 16;
		i++;
	}
	hex[i] = '\0';
	ft_print_rev_str(hex);
	free(hex);
	return (ft_print_rev_str(hex) - 1);
}

int	ft_print_ptr(size_t ptr)
{
	int	rem;
	int	i;
	char	*hex;
	
	i = 0;
	hex = malloc(sizeof(char) * 100);
	while (ptr > 0)
	{
		rem = ptr % 16;
		if (rem < 10)
			hex[i] = rem + 48;
		else
			hex[i] = rem + 55;
		ptr = ptr / 16;
		i++;
	}
	hex[i] = '\0';
	ft_print_rev_str(hex);
	free(hex);
	return (ft_print_rev_str(hex) - 1);
}

unsigned int	multidiv(unsigned int len)
{
	unsigned int	div;

	div = 1;
	while (len > 1)
	{
		div *= 10;
		len--;
	}
	return (div);
}

int	ft_print_int(int n)
{
	unsigned int	len;
	unsigned int	div;
	unsigned int	num;
	char			c;

	len = check_len(n);
	if (n < 0)
	{
		write(1, "-", 1);
		num = -n;
		len -= 1;
	}
	else
		num = n;
	div = multidiv(len);
	while (len > 0)
	{
		c = num / div;
		num -= c * div;
		c += 48;
		write(1, &c, 1);
		div = div / 10;
		len--;
	}
	return (check_len(n) - 1);
}

int	ft_print_u(unsigned int n)
{
	unsigned int	len;
	unsigned int	div;
	unsigned int	num;
	char			c;
	
	len = check_len(n);
	num = n;
	div = multidiv(len);
	while (len > 0)
	{
		c = num / div;
		num -= c * div;
		c += 48;
		write(1, &c, 1);
		div = div / 10;
		len--;
	}
	return (check_len(n) - 1);
}

int	ft_print_hex_low(unsigned int num)
{
	unsigned int	rem;
	int	i;
	char	*hex;
	
	i = 0;
	hex = malloc(sizeof(char) * 100);
	while (num > 0)
	{
		rem = num % 16;
		if (rem < 10)
			hex[i] = rem + 48;
		else
			hex[i] = rem + 87;
		num = num / 16;
		i++;
	}
	hex[i] = '\0';
	ft_print_rev_str(hex);
	free(hex);
	return (ft_print_rev_str(hex) - 1);
}

int	ft_check_cond(va_list args, const char c)
{
	int	len;

	len = 0;
	if (c == 'c')
		len = ft_print_char(va_arg(args, int));
	else if (c == 's')
		len = ft_print_str(va_arg(args, char *));
	else if (c == 'p')
	{
		write(1, "0x", 2);
		len = 2 + ft_print_hex_low(va_arg(args, size_t));
	}
	else if (c == 'd' || c == 'i')
		len = ft_print_int(va_arg(args, int));
	else if (c == 'u')
		len = ft_print_u(va_arg(args, unsigned int));
	else if (c == 'x')
		len = ft_print_hex_low(va_arg(args, unsigned int));
	else if (c == 'X')
		len = ft_print_hex_up(va_arg(args, unsigned int));
	else if (c == '%')
	{
		write(1, '%', 1)
		len = 1;
	}
	return (len);
}

int	ft_printf(const char* format, ...)
{
	va_list va_arg;
	int	i;
	int	len;
	
	i = 0;
	len = 0;
	va_start(va_arg, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			len += ft_check_cond(va_arg, format[i]);
			i++;
		}
		else
		{
			write(1, &format[i], 1);
			len++;
		}
		i++;
	}
	va_end(va_arg);
	return (len);
}



























