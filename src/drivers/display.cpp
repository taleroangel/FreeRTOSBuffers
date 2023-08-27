#include "display.hxx"

#include <cstdio>
#include <cstring>

namespace drivers {

bool display::set(section_id_t section, segment_mask_t value) {
  // Check errors
  if (section > DISPLAY_NUMBER_OF_SECTIONS || section == 0U)
    return false;

  // Write contents
  sections[section - 1] = value;

  return true;
}

void display::set(segment_mask_t section_data[DISPLAY_NUMBER_OF_SECTIONS]) {
  std::memcpy(sections, section_data, DISPLAY_NUMBER_OF_SECTIONS);
}

void display::set(char content[DISPLAY_NUMBER_OF_SECTIONS + 1],
                  std::size_t content_size) {
  // Clear the display
  empty();

  // Write content to display backwards
  for (unsigned int i = 1; i <= DISPLAY_NUMBER_OF_SECTIONS; i++) {
	// Get the char as segment mask
    segment_mask_t data = interpret_symbol(content[content_size - i]);
	// Set the section data
    sections[DISPLAY_NUMBER_OF_SECTIONS - i] = data;
  }
}
void display::push(segment_mask_t value) {
  // Move values to the left
  for (unsigned int i = 0; i < DISPLAY_NUMBER_OF_SECTIONS - 1; i++)
    sections[i] = sections[i + 1];
  // Change last section
  sections[DISPLAY_NUMBER_OF_SECTIONS - 1] = value;
}

bool display::unset(section_id_t section) {
  // Check errors
  if (section > DISPLAY_NUMBER_OF_SECTIONS || section == 0U)
    return false;

  // Write contents
  sections[section - 1] = 0U;

  return true;
}

void display::clear() {
  current_section = 0;
  empty(); // Clear segment data
}

void display::update() {
  // Go to next section
  current_section = (current_section % DISPLAY_NUMBER_OF_SECTIONS) + 1U;
  // Render it
  render();
}

void display::init() const {
  // Initialize the segments
  gpio_pin_config_t segmentConfig{kGPIO_DigitalOutput, DISPLAY_SEGMENT_OFF};
  GPIO_PinInit(DISPLAY_SEGMENT_A_GPIO, DISPLAY_SEGMENT_A_PIN, &segmentConfig);
  GPIO_PinInit(DISPLAY_SEGMENT_B_GPIO, DISPLAY_SEGMENT_B_PIN, &segmentConfig);
  GPIO_PinInit(DISPLAY_SEGMENT_C_GPIO, DISPLAY_SEGMENT_C_PIN, &segmentConfig);
  GPIO_PinInit(DISPLAY_SEGMENT_D_GPIO, DISPLAY_SEGMENT_D_PIN, &segmentConfig);
  GPIO_PinInit(DISPLAY_SEGMENT_E_GPIO, DISPLAY_SEGMENT_E_PIN, &segmentConfig);
  GPIO_PinInit(DISPLAY_SEGMENT_F_GPIO, DISPLAY_SEGMENT_F_PIN, &segmentConfig);
  GPIO_PinInit(DISPLAY_SEGMENT_G_GPIO, DISPLAY_SEGMENT_G_PIN, &segmentConfig);

  // Initialize the sections
  gpio_pin_config_t sectionConfig{kGPIO_DigitalOutput, DISPLAY_SECTION_OFF};
  GPIO_PinInit(DISPLAY_SECTION_1_GPIO, DISPLAY_SECTION_1_PIN, &sectionConfig);
  GPIO_PinInit(DISPLAY_SECTION_2_GPIO, DISPLAY_SECTION_2_PIN, &sectionConfig);
  GPIO_PinInit(DISPLAY_SECTION_3_GPIO, DISPLAY_SECTION_3_PIN, &sectionConfig);
}

void display::render() const {
  // Get the current mask
  const auto mask = sections[current_section - 1];

  // Enable section and disable others
  GPIO_PinWrite(DISPLAY_SECTION_1_GPIO, DISPLAY_SECTION_1_PIN,
                (current_section == 1) ? DISPLAY_SECTION_ON
                                       : DISPLAY_SECTION_OFF);
  GPIO_PinWrite(DISPLAY_SECTION_2_GPIO, DISPLAY_SECTION_2_PIN,
                (current_section == 2) ? DISPLAY_SECTION_ON
                                       : DISPLAY_SECTION_OFF);
  GPIO_PinWrite(DISPLAY_SECTION_3_GPIO, DISPLAY_SECTION_3_PIN,
                (current_section == 3) ? DISPLAY_SECTION_ON
                                       : DISPLAY_SECTION_OFF);

  // Ignore section
  if (current_section == 0)
    return;

  // Write to every pin
  GPIO_PinWrite(DISPLAY_SEGMENT_A_GPIO, DISPLAY_SEGMENT_A_PIN,
                (mask & DISPLAY_MASK_SEGMENT_A) != 0U ? DISPLAY_SEGMENT_ON
                                                      : DISPLAY_SEGMENT_OFF);
  GPIO_PinWrite(DISPLAY_SEGMENT_B_GPIO, DISPLAY_SEGMENT_B_PIN,
                (mask & DISPLAY_MASK_SEGMENT_B) != 0U ? DISPLAY_SEGMENT_ON
                                                      : DISPLAY_SEGMENT_OFF);
  GPIO_PinWrite(DISPLAY_SEGMENT_C_GPIO, DISPLAY_SEGMENT_C_PIN,
                (mask & DISPLAY_MASK_SEGMENT_C) != 0U ? DISPLAY_SEGMENT_ON
                                                      : DISPLAY_SEGMENT_OFF);
  GPIO_PinWrite(DISPLAY_SEGMENT_D_GPIO, DISPLAY_SEGMENT_D_PIN,
                (mask & DISPLAY_MASK_SEGMENT_D) != 0U ? DISPLAY_SEGMENT_ON
                                                      : DISPLAY_SEGMENT_OFF);
  GPIO_PinWrite(DISPLAY_SEGMENT_E_GPIO, DISPLAY_SEGMENT_E_PIN,
                (mask & DISPLAY_MASK_SEGMENT_E) != 0U ? DISPLAY_SEGMENT_ON
                                                      : DISPLAY_SEGMENT_OFF);
  GPIO_PinWrite(DISPLAY_SEGMENT_F_GPIO, DISPLAY_SEGMENT_F_PIN,
                (mask & DISPLAY_MASK_SEGMENT_F) != 0U ? DISPLAY_SEGMENT_ON
                                                      : DISPLAY_SEGMENT_OFF);
  GPIO_PinWrite(DISPLAY_SEGMENT_G_GPIO, DISPLAY_SEGMENT_G_PIN,
                (mask & DISPLAY_MASK_SEGMENT_G) != 0U ? DISPLAY_SEGMENT_ON
                                                      : DISPLAY_SEGMENT_OFF);
}

void display::empty() { std::memset(sections, 0U, DISPLAY_NUMBER_OF_SECTIONS); }

display::segment_mask_t display::interpret_symbol(char symbol) {
  switch (symbol) {
    /* --------- Numbers --------- */
  case '0':
  case 'O': // Letter
    return 0b01111110;
  case '1':
  case 'I': // Letter
    return 0b00110000;
  case '2':
    return 0b01101101;
  case '3':
    return 0b01111001;
  case '4':
    return 0b00110011;
  case '5':
  case 'S': // Letter
  case 's':
    return 0b01011011;
  case '6':
    return 0b01011111;
  case '7':
    return 0b01110000;
  case '8':
    return 0b01111111;
  case '9':
  case 'g': // Letter

    return 0b01111011;
    /* --------- Letters --------- */
  case 'a':
  case 'A':
    return 0b01110111;
  case 'b':
  case 'B':
    return 0b00011111;
  case 'c':
    return 0b01001110;
  case 'C':
  case '(': // Special character
  case '[': // Special character
  case '{': // Special character
    return 0b01001110;
  case 'd':
  case 'D':
    return 0b00111101;
  case 'E':
  case 'e':
    return 0b01001111;
  case 'F':
  case 'f':
    return 0b01000111;
  case 'G':
    return 0b01011110;
  case 'h':
    return 0b00010111;
  case 'H':
    return 0b00110111;
  case 'i':
    return 0b01010000;
  case 'j':
    return 0b01011000;
  case 'l':
    return 0b00000110;
  case 'L':
    return 0b00001110;
  case 'm':
  case 'M':
    return 0b00110110;
  case 'n':
    return 0b00010101;
  case 'N':
    return 0b01110110;
  case 'o':
    return 0b00011101;
  case 'p':
  case 'P':
    return 0b01100111;
  case 'q':
  case 'Q':
    return 0b01110011;
  case 'r':
  case 'R':
    return 0b00000101;
  case 't':
  case 'T':
    return 0b0000111;
  case 'u':
  case 'v':
    return 0b00011100;
  case 'U':
    return 0b00111110;
  case 'V':
    return 0b00101010;
  case 'x':
  case 'X':
    return 0b00110111;
  case 'y':
    return 0b00111011;
  case 'Y':
    return 0b00101011;
  case 'z':
  case 'Z':
    return 0b01101100;

  /* --------- Special characters --------- */
  case ')':
  case ']':
  case '}':
    return 0b01111000;
  case '\\':
    return 0b00010010;
  case '/':
    return 0b00100100;
  case '-':
    return 0b00000001;
  case '_':
    return 0b00001000;

  /* --------- Default --------- */
  case ' ':
    return 0b00000000;
  default:
    return 0b10000000; // Just the Error flag
  }
}
} // namespace drivers