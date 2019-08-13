declare module '*.twig' {
    const content: (context: any) => string;
    export default content;
}
