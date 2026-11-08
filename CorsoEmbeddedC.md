# Corso Embedded C

## Settare i bit nei registri
reg |= (1 << n);     // Set bit n
reg &= ~(1 << n);    // Clear bit n
reg ^= (1 << n);     // Toggle bit n
if (reg & (1 << n))  // Check if bit n is set
