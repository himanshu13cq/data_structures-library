# Build Log 5

## Date: 10/07/2026

### Session - 1

## Research: Implementing `default_hash` for user-defined types

When implementing a default hash function for a user-defined type, two common approaches are often considered:

1. Hash the object address.
2. Hash the raw bytes of the object.

### Problem with using the object address

- The address of an object is not stable across separate objects with the same value.
- For user-defined types, two objects with equal fields can reside at different heap addresses.
- This means the hash would differ for logically equal values, breaking the hash contract.

### Problem with hashing raw bytes

Two main issues arise:

- Padding bytes: compiler-added padding inside structs or classes may contain indeterminate data.
  - These padding bytes can differ between otherwise equal objects.
  - Hashing raw memory can therefore produce different results for equal values.
- Dynamic allocation: if the type contains pointers or owning resources (like `std::string`, `std::vector`, or other heap allocations), hashing the raw object memory does not account for the pointed-to data.
  - The raw bytes only include pointer values, not the contents of the dynamically allocated memory.
  - As a result, different objects with equal deep content can yield different hashes.

### Conclusion

A safe default hash for user-defined types should:

- Use field-by-field hashing of the logical value.
- Avoid hashing addresses.
- Avoid hashing raw bytes directly when the type contains padding or dynamic data.

This research motivates implementing `default_hash` as a composition of hashes for each relevant member rather than relying on object addresses or raw memory dumps.