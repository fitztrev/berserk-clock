<script setup lang="ts">
const props = defineProps<{
  step: number
}>()
</script>

<template>
  <div class="font-[Lichess] text-slate-300">
    <template v-if="props.step > 0"> &#57414;</template>
    <template v-else> &#57413; </template>
  </div>
</template>
