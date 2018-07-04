# reason-maybe
A simple Maybe library in Reason.

[![forthebadge](https://forthebadge.com/images/badges/gluten-free.svg)](https://forthebadge.com)
[![forthebadge](https://forthebadge.com/images/badges/built-with-love.svg)](https://forthebadge.com)

[![Made with Reason](https://img.shields.io/badge/Made%20with-Reason-red.svg?longCache=true&style=for-the-badge)](https://reasonml.github.io/)

## Installation
- Install [Yarn](https://yarnpkg.com).
- Run `yarn add reason-maybe`.
- Add `reason-maybe` to your `bs-dependencies` in `bsconfig.json`

**`bsconfig.json`**
```json
"bs-dependencies": [
  "reason-maybe"
]
```

## Usage

### `from`
To create a Maybe use `Maybe.from`:
```reason
let one = Maybe.from(Some(1)); /* Just(1) */
```

### `map`
To map a function on the Maybe, use `Maybe.map`:
```reason
let plusOne = x => x + 1;
let onePlusOne = one |> Maybe.map(plusOne); /* Just(2) */
```

If the map provides a value, it will return `Just(value)`. Else, it will return a `Nothing`.

### `value`
To extract the value of the Maybe, we need to use `Maybe.value`:
```reason
let value = onePlusOne |> Maybe.value(0); /* 2 */
```

If the Maybe was actually a `Nothing`, the value given to the `Maybe.value` function will be the resulting value.
In this case if `onePlusOne` was `Nothing`, the value of `value` would be `0`.

### `chain`
To run a function that returns a Maybe on a Maybe, we use `Maybe.chain`:
```reason
let two = Maybe.from(Some(2));
let plusOneMaybe = x => one |> Maybe.map(y => x + y);
let twoPlusOneMaybe = two |> Maybe.chain(plusOneMaybe); /* Just(3) */
```

We use the `plusOneMaybe` function which returns a Maybe on the `two` Maybe.
Instead of `Maybe.map`, we use `Maybe.chain` to lift it from the returned Maybe unto the current Maybe.

## Development

1. Clone this repo.
2. Move to this directory with `cd reason-maybe`.
3. Install [Yarn](https://yarnpkg.com).
4. Run `yarn`.

### Build
```
npm run build
```

### Build + Watch

```
npm run start
```

## License
MIT